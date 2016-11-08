#include "TextureEditorWidget.h"

namespace ofx {
namespace piMapper {

TextureEditorWidget::TextureEditorWidget(){
	_pollCreateJoints = false;
	
	clear();
}

void TextureEditorWidget::setup(){
	// Nothing here yet.
}

void TextureEditorWidget::update(){
	if(surface == 0){
		return;
	}
	
	if(_pollCreateJoints){
		createJoints();
	}

	// update surface if one of the joints is being dragged
	ofVec2f textureSize = ofVec2f(surface->getSource()->getTexture()->getWidth(),
								  surface->getSource()->getTexture()->getHeight());

	// Get selected joint index
	int selectedJointIndex = 0;
	bool bJointSelected = false;
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isDragged() || joints[i]->isSelected()){
			selectedJointIndex = i;
			bJointSelected = true;
			break;
		}
	} // for

	// Constrain quad texture selection
	if(joints.size() == 4){
		if(bJointSelected){
			constrainJointsToQuad(selectedJointIndex);

			if(surface->getType() == SurfaceType::GRID_WARP_SURFACE){
				GridWarpSurface * s = (GridWarpSurface *)surface;
				vector <ofVec2f> & texCoords = surface->getTexCoords();
				ofVec2f textureSize = ofVec2f(surface->getSource()->getTexture()->getWidth(),
									  surface->getSource()->getTexture()->getHeight());
		
				int rows = s->getGridRows();
				int cols = s->getGridCols();
				int vertsPerRow = cols + 1;
				
				// Distance between horizontal tex coords
				float sx = joints[0]->position.x / textureSize.x;
				float ex = joints[1]->position.x / textureSize.x;
				float dx = (ex - sx) / (float)cols;
		
				// Distance between vertical tex coords
				float sy = joints[0]->position.y / textureSize.y;
				float ey = joints[2]->position.y / textureSize.y;
				float dy = (ey - sy) / (float)rows;
		
				int i = 0;
				for(int iy = 0; iy <= rows; ++iy){
					for(int ix = 0; ix <= cols; ++ix){
						ofVec2f t;
						t.x = sx + dx * ix;
						t.y = sy + dy * iy;
						surface->setTexCoord(i, t);
						++i;
					}
				}
			}else{
				for(int i = 0; i < joints.size(); i++){
					surface->setTexCoord(i, joints[i]->position / textureSize);
				}
			}
		} // if
	}else{
		if(bJointSelected){
			surface->setTexCoord(selectedJointIndex, joints[selectedJointIndex]->position / textureSize);
		}
	} // else
}

void TextureEditorWidget::onMousePressed(ofMouseEventArgs & args){
	for(unsigned int i = 0; i < joints.size(); ++i){
		joints[i]->mousePressed(args);
	}
}

void TextureEditorWidget::onMouseReleased(ofMouseEventArgs & args){
	// Nothing
}

void TextureEditorWidget::onMouseDragged(ofMouseEventArgs & args){
	for(unsigned int i = 0; i < joints.size(); ++i){
		joints[i]->mouseDragged(args);
	}
}

void TextureEditorWidget::draw(){
	if(surface == 0){
		return;
	}

	// Reset default color to white
	ofSetColor(255, 255, 255, 255);
	drawJoints();
}

void TextureEditorWidget::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->draw();
	}
}

void TextureEditorWidget::setSurface(BaseSurface * newSurface){
	surface = newSurface;
	createJoints();
}

void TextureEditorWidget::clear(){
	surface = 0;
	clearJoints();
}

void TextureEditorWidget::createJoints(){
	if(surface == 0){
		return;
	}
	clearJoints();
	vector <ofVec2f> & texCoords = surface->getTexCoords();
	
	if(surface->getSource()->getTexture()->isAllocated()){
		_pollCreateJoints = false;
	}else{
		_pollCreateJoints = true;
		return;
	}
	
	ofVec2f textureSize = ofVec2f(surface->getSource()->getTexture()->getWidth(),
								  surface->getSource()->getTexture()->getHeight());
	
	// Select joints depending on the surface type
	vector <ofVec2f> tc;
	
	if(surface->getType() == SurfaceType::TRIANGLE_SURFACE){
		tc = texCoords;
	}else if(surface->getType() == SurfaceType::QUAD_SURFACE){
		tc = texCoords;
	}else if(surface->getType() == SurfaceType::HEXAGON_SURFACE){
		tc = texCoords;
	}else if(surface->getType() == SurfaceType::GRID_WARP_SURFACE){
		GridWarpSurface * s = (GridWarpSurface *)surface;
		
		int rows = s->getGridRows();
		int cols = s->getGridCols();
		int vertsPerRow = cols + 1;
		int vertsPerCol = rows + 1;
		
		int a = 0;
		int b = cols;
		int c = (rows * vertsPerRow) + (vertsPerRow - 1);
		int d = (rows * vertsPerRow);
		
		tc.push_back(texCoords[a]);
		tc.push_back(texCoords[b]);
		tc.push_back(texCoords[c]);
		tc.push_back(texCoords[d]);
	}

	for(int i = 0; i < tc.size(); i++){
		joints.push_back(new CircleJoint());
		joints.back()->position = tc[i] * textureSize;
	}
}

void TextureEditorWidget::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}

void TextureEditorWidget::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void TextureEditorWidget::selectTexCoord(int i){
	if(joints.size() <= 0){
		return;
	}
	
	if(i >= (int)joints.size()){
		ofLogError("TextureEditorWidget::selectTexCoord",
			"Attempt to select non existent tex coord");
		return;
	}
	
	unselectAllJoints();
	
	if(i >= 0){
		joints[i]->select();
	}
}

int TextureEditorWidget::getSelectedTexCoord(){
	if(joints.size() <= 0){
		return -1;
	}
	
	for(unsigned int i = 0; i < joints.size(); ++i){
		if(joints[i]->isSelected()){
			return i;
		}
	}
	
	return -1;
}

void TextureEditorWidget::selectNextTexCoord(){
	if(joints.size() <= 0){
		return;
	}
	
	// Search for current selected joint
	for(unsigned int i = 0; i < joints.size(); ++i){
		if(joints[i]->isSelected()){
			unsigned int next = i + 1;
			if(next >= joints.size()){
				next = 0;
			}
			unselectAllJoints();
			//joints[next]->select();
			selectTexCoord(next);
			return;
		}
	}
	
	// If none found, select 0th
	//joints[0]->select();
	selectTexCoord(0);
}

void TextureEditorWidget::selectPrevTexCoord(){
	if(joints.size() <= 0){
		return;
	}
	
	// Search for current selected joint
	for(unsigned int i = 0; i < joints.size(); ++i){
		if(joints[i]->isSelected()){
			unsigned int prev;
			if(i == 0){
				prev = joints.size() - 1;
			}else{
				prev = i - 1;
			}
			unselectAllJoints();
			//joints[prev]->select();
			selectTexCoord(prev);
			return;
		}
	}
	
	// Select last if none selected
	//joints[joints.size() - 1]->select();
	selectTexCoord(joints.size() - 1);
}

void TextureEditorWidget::moveTexCoords(ofVec2f by){
	if(surface == 0){
		return;
	}

	vector <ofVec2f> & texCoords = surface->getTexCoords();
	ofVec2f textureSize = ofVec2f(surface->getSource()->getTexture()->getWidth(),
								  surface->getSource()->getTexture()->getHeight());
	
	for(int i = 0; i < joints.size(); i++){
		joints[i]->position += by;
	}
	
	if(surface->getType() == SurfaceType::GRID_WARP_SURFACE){
		GridWarpSurface * s = (GridWarpSurface *)surface;
		
		int rows = s->getGridRows();
		int cols = s->getGridCols();
		int vertsPerRow = cols + 1;
		int vertsPerCol = rows + 1;
		
		int a = 0;
		int b = cols;
		int c = (rows * vertsPerRow) + (vertsPerRow - 1);
		int d = (rows * vertsPerRow);
		
		// Distance between horizontal tex coords
		float sx = joints[0]->position.x / textureSize.x;
		float ex = joints[1]->position.x / textureSize.x;
		float dx = (ex - sx) / (float)cols;
		
		// Distance between vertical tex coords
		float sy = joints[0]->position.y / textureSize.y;
		float ey = joints[2]->position.y / textureSize.y;
		float dy = (ey - sy) / (float)rows;
		
		int i = 0;
		for(int iy = 0; iy <= rows; ++iy){
			for(int ix = 0; ix <= cols; ++ix){
				ofVec2f t;
				t.x = sx + dx * ix;
				t.y = sy + dy * iy;
				surface->setTexCoord(i, t);
				++i;
			}
		}
	}else{
		for(int i = 0; i < texCoords.size(); i++){
			surface->setTexCoord(i, joints[i]->position / textureSize);
		}
	}
}

void TextureEditorWidget::moveTexCoordTo(int texCoordIndex, ofVec2f position){
	if(surface == 0){
		return;
	}
	
	ofLogNotice("TextureEditorWidget::moveTexCoordTo") << texCoordIndex << ", " << position.x << ", " << position.y;
	surface->setTexCoord(texCoordIndex, position);
	
	ofVec2f textureSize = ofVec2f(
		surface->getSource()->getTexture()->getWidth(),
		surface->getSource()->getTexture()->getHeight());
	joints[texCoordIndex]->position = position * textureSize;
}

void TextureEditorWidget::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void TextureEditorWidget::moveSelection(ofVec2f by){
	// check if joints selected
	bool bJointSelected = false;
	BaseJoint * selectedJoint;
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->isSelected()){
			bJointSelected = true;
			selectedJoint = joints[i];
			break;
		}
	}

	if(bJointSelected){
		selectedJoint->position += by;
	}else{
		moveTexCoords(by);
	}
}

void TextureEditorWidget::constrainJointsToQuad(int selectedJointIndex){
	switch(selectedJointIndex){
	 case 0:
		 joints[1]->position = ofVec2f(joints[1]->position.x, joints[0]->position.y);
		 joints[2]->position = ofVec2f(joints[1]->position.x, joints[3]->position.y);
		 joints[3]->position = ofVec2f(joints[0]->position.x, joints[3]->position.y);
		 break;

	 case 1:
		 joints[0]->position = ofVec2f(joints[0]->position.x, joints[1]->position.y);
		 joints[2]->position = ofVec2f(joints[1]->position.x, joints[2]->position.y);
		 joints[3]->position = ofVec2f(joints[0]->position.x, joints[2]->position.y);
		 break;

	 case 2:
		 joints[1]->position = ofVec2f(joints[2]->position.x, joints[1]->position.y);
		 joints[3]->position = ofVec2f(joints[3]->position.x, joints[2]->position.y);
		 joints[0]->position = ofVec2f(joints[3]->position.x, joints[1]->position.y);
		 break;

	 case 3:
		 joints[0]->position = ofVec2f(joints[3]->position.x, joints[0]->position.y);
		 joints[2]->position = ofVec2f(joints[2]->position.x, joints[3]->position.y);
		 joints[1]->position = ofVec2f(joints[2]->position.x, joints[0]->position.y);
		 break;
	} // switch
}

CircleJoint * TextureEditorWidget::hitTestJoints(ofVec2f pos){
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

vector <CircleJoint *> & TextureEditorWidget::getJoints(){
	return joints;
}

} // namespace piMapper
} // namespace ofx