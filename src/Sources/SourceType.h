#pragma once

#include "ofLog.h"

#define SOURCE_TYPE_NAME_NONE "none"
#define SOURCE_TYPE_NAME_IMAGE "image"
#define SOURCE_TYPE_NAME_VIDEO "video"

namespace ofx {
  namespace piMapper {
    class SourceType {
    public:
      enum { SOURCE_TYPE_NONE, SOURCE_TYPE_IMAGE, SOURCE_TYPE_VIDEO };
      
      static std::string GetSourceTypeName(int sourceTypeEnum) {
        if (sourceTypeEnum == SOURCE_TYPE_IMAGE) {
          return SOURCE_TYPE_NAME_IMAGE;
        } else if (sourceTypeEnum == SOURCE_TYPE_VIDEO) {
          return SOURCE_TYPE_NAME_VIDEO;
        } else if (sourceTypeEnum == SOURCE_TYPE_NONE) {
          return SOURCE_TYPE_NAME_NONE;
        } else {
          std::stringstream ss;
          ss << "Invalid source type: " << sourceTypeEnum;
          ofLogFatalError("SourceType") << ss.str();
          std::exit(EXIT_FAILURE);
        }
      };
      
      static int GetSourceTypeEnum(std::string sourceTypeName) {
        if (sourceTypeName == SOURCE_TYPE_NAME_IMAGE) {
          return SOURCE_TYPE_IMAGE;
        } else if (sourceTypeName == SOURCE_TYPE_NAME_VIDEO) {
          return SOURCE_TYPE_VIDEO;
        } else if (sourceTypeName == SOURCE_TYPE_NAME_NONE) {
          return SOURCE_TYPE_NONE;
        } else {
          std::stringstream ss;
          ss << "Invalid source type name: " << sourceTypeName;
          ofLogFatalError("SourceType") << ss.str();
          std::exit(EXIT_FAILURE);
        }
      }
    };
  }
}