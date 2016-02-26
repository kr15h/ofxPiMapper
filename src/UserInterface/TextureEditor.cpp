#include "TextureEditor.h"

namespace ofx {
namespace piMapper {

TextureEditor::TextureEditor(){
	clear();
	enable();
}

TextureEditor::~TextureEditor(){
	clear();
	disable();
}

void TextureEditor::registerAppEvents(){
	ofAddListener(ofEvents().update, this, &TextureEditor::update);
}

void TextureEditor::unregisterAppEvents(){
	ofRemoveListener(ofEvents().update, this, &TextureEditor::update);
}

void TextureEditor::registerKeyEvents(){
	ofAddListener(ofEvents().keyPressed, this, &TextureEditor::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &TextureEditor::keyReleased);
}

void TextureEditor::unregisterKeyEvents(){
	ofRemoveListener(ofEvents().keyPressed, this, &TextureEditor::keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &TextureEditor::keyReleased);
}

void TextureEditor::enable(){
	registerAppEvents();
	registerKeyEvents();
	bShiftKeyDown = false;
}

void TextureEditor::disable(){
	unregisterAppEvents();
	unregisterKeyEvents();
}

void TextureEditor::update(ofEventArgs & args){
	if(surface == 0){
		return;
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

void TextureEditor::keyPressed(ofKeyEventArgs & args){
	int key = args.key;
	float moveStep;

	if(bShiftKeyDown){
		moveStep = 10.0f;
	}else{
		moveStep = 0.5f;
	}

	switch(key){
	 case OF_KEY_LEFT:
		 moveSelection(ofVec2f(-moveStep, 0.0f));
		 break;

	 case OF_KEY_RIGHT:
		 moveSelection(ofVec2f(moveStep, 0.0f));
		 break;

	 case OF_KEY_UP:
		 moveSelection(ofVec2f(0.0f, -moveStep));
		 break;

	 case OF_KEY_DOWN:
		 moveSelection(ofVec2f(0.0f, moveStep));
		 break;

	 case OF_KEY_SHIFT:
		 bShiftKeyDown = true;
		 break;
	}
}

void TextureEditor::keyReleased(ofKeyEventArgs & args){
	int key = args.key;
	switch(key){
	 case OF_KEY_SHIFT:
		 bShiftKeyDown = false;
		 break;
	}
}

void TextureEditor::draw(){
	if(surface == 0){
		return;
	}

	// Reset default color to white
	ofSetColor(255, 255, 255, 255);
	drawJoints();
}

void TextureEditor::drawJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->draw();
	}
}

void TextureEditor::setSurface(BaseSurface * newSurface){
	surface = newSurface;
	createJoints();
}

void TextureEditor::clear(){
	surface = 0;
	clearJoints();
}

void TextureEditor::createJoints(){
	if(surface == 0){
		return;
	}
	clearJoints();
	vector <ofVec2f> & texCoords = surface->getTexCoords();
	ofVec2f textureSize = ofVec2f(surface->getSource()->getTexture()->getWidth(),
								  surface->getSource()->getTexture()->getHeight());
	
	// Select joints depending on the surface type
	vector <ofVec2f> tc;
	
	if(surface->getType() == SurfaceType::TRIANGLE_SURFACE){
		tc = texCoords;
	}else if(surface->getType() == SurfaceType::QUAD_SURFACE){
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

void TextureEditor::clearJoints(){
	while(joints.size()){
		delete joints.back();
		joints.pop_back();
	}
}

void TextureEditor::unselectAllJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->unselect();
	}
}

void TextureEditor::selectNextTexCoord(){
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
			joints[next]->select();
			return;
		}
	}
	
	// If none found, select 0th
	joints[0]->select();
}

void TextureEditor::selectPrevTexCoord(){
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
			joints[prev]->select();
			return;
		}
	}
	
	// Select last if none selected
	joints[joints.size() - 1]->select();
}

void TextureEditor::moveTexCoords(ofVec2f by){
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

void TextureEditor::stopDragJoints(){
	for(int i = 0; i < joints.size(); i++){
		joints[i]->stopDrag();
	}
}

void TextureEditor::moveSelection(ofVec2f by){
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

void TextureEditor::constrainJointsToQuad(int selectedJointIndex){
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

CircleJoint * TextureEditor::hitTestJoints(ofVec2f pos){
	for(int i = 0; i < joints.size(); i++){
		if(joints[i]->hitTest(pos)){
			return joints[i];
		}
	}
	return 0;
}

vector <CircleJoint *> & TextureEditor::getJoints(){
	return joints;
}

} // namespace piMapper
} // namespace ofx