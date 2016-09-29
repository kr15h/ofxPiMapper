#include "ApplicationBaseMode.h"
#include "PresentationMode.h"

namespace ofx {
namespace piMapper {

void ApplicationBaseMode::setState(Application * app, ApplicationBaseMode * st){
	app->setState(st);
}

} // namespace piMapper
} // namespace ofx
