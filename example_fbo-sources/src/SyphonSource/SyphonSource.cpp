// #include "SyphonSource.h"
//
// void SyphonSource::setup(){
// 	// Give our source a decent name
// 	name = "Syphon Source";
//
// 	// Allocate our FBO source, decide how big it should be
// 	allocate(500, 500);
//
// 	//setup our directory
// 	dir.setup();
// 	//setup our client
// 	mClient.setup();
//
// 	//register for our directory's callbacks
// 	ofAddListener(dir.events.serverAnnounced, this, &SyphonSource::serverAnnounced);
// 	// not yet implemented
// 	//ofAddListener(dir.events.serverUpdated, this, &ofApp::serverUpdated);
// 	ofAddListener(dir.events.serverRetired, this, &SyphonSource::serverRetired);
//
// 	dirIdx = -1;
// }
//
// //these are our directory's callbacks
// void SyphonSource::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
// {
// 	for( auto& dir : arg.servers ){
// 			ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
// 	}
// 	dirIdx = 0;
// }
//
// void SyphonSource::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
// {
// 	for( auto& dir : arg.servers ){
// 			ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
// 	}
// 	dirIdx = 0;
// }
//
// void SyphonSource::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
// {
// 	for( auto& dir : arg.servers ){
// 			ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
// 	}
// 	dirIdx = 0;
// }
//
//
// // Don't do any drawing here
// void SyphonSource::update(){
//
// }
//
// // No need to take care of fbo.begin() and fbo.end() here.
// // All within draw() is being rendered into fbo;
// void SyphonSource::draw(){
// 	if(dir.isValidIndex(dirIdx))
// 			mClient.draw(0, 0);
// }
//
// //--------------------------------------------------------------
// void SyphonSource::keyReleased(int key){
//     //press any key to move through all available Syphon servers
//     if (dir.size() > 0)
//     {
//         dirIdx++;
//         if(dirIdx > dir.size() - 1)
//             dirIdx = 0;
//
//         mClient.set(dir.getDescription(dirIdx));
//         string serverName = mClient.getServerName();
//         string appName = mClient.getApplicationName();
//
//         if(serverName == ""){
//             serverName = "null";
//         }
//         if(appName == ""){
//             appName = "null";
//         }
//         ofSetWindowTitle(serverName + ":" + appName);
//     }
//     else
//     {
//         ofSetWindowTitle("No Server");
//     }
// }
