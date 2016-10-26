#THIS FILE SHOULD BE PUT INTO THE OF PROJECT FOLDER

# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required( VERSION 3.3 )
project( openframeworks )

# ========================================================
# ===================== User Settings ====================
# ========================================================
# ---------------------- App name  -----------------------
set( APP_NAME   example_camera_ofxPiMapper )

# ------------------------ OF Path -----------------------
# --- If outside the OF stucture, set an absolute OF path
set( OF_DIRECTORY_BY_USER "../../.." )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofApp.cpp
        src/CameraSource.cpp)


# ------------------------ AddOns  -----------------------
set( OFX_ADDONS_ACTIVE
                ofxXmlSettings
                ofxGui
                ofxPiMapper
                ofxIO
                )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================

