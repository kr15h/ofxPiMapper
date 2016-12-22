#pragma once

#include "ofLog.h"

#define SOURCE_TYPE_NAME_NONE "none"
#define SOURCE_TYPE_NAME_IMAGE "image"
#define SOURCE_TYPE_NAME_VIDEO "video"
#define SOURCE_TYPE_NAME_FBO "fbo"

namespace ofx {
namespace piMapper {

class SourceType {

	public:
		enum {
			SOURCE_TYPE_NONE, SOURCE_TYPE_IMAGE, SOURCE_TYPE_VIDEO, SOURCE_TYPE_FBO
		};

		static string GetSourceTypeName(int sourceTypeEnum){
			if(sourceTypeEnum == SOURCE_TYPE_IMAGE){
				return SOURCE_TYPE_NAME_IMAGE;
			}else if(sourceTypeEnum == SOURCE_TYPE_VIDEO){
				return SOURCE_TYPE_NAME_VIDEO;
			}else if(sourceTypeEnum == SOURCE_TYPE_NONE){
				return SOURCE_TYPE_NAME_NONE;
			}else if(sourceTypeEnum == SOURCE_TYPE_FBO){
				return SOURCE_TYPE_NAME_FBO;
			}else{
				std::string out;
				out + "Invalid source type: " + std::to_string(sourceTypeEnum);
				ofLogFatalError("SourceType " + out);
				exit(EXIT_FAILURE);
			}
		}

		static int GetSourceTypeEnum(string sourceTypeName){
			if(sourceTypeName == SOURCE_TYPE_NAME_IMAGE){
				return SOURCE_TYPE_IMAGE;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_VIDEO){
				return SOURCE_TYPE_VIDEO;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_NONE){
				return SOURCE_TYPE_NONE;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_FBO){
				return SOURCE_TYPE_FBO;
			}else{
				std::string out;
				out + "Invalid source type name: " + sourceTypeName;
				ofLogFatalError("SourceType " + out);
				exit(EXIT_FAILURE);
			}
		}

};

} // namespace piMapper
} // namespace ofx