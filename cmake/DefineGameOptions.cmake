OPTION(NO_SOUND "Turn off sound support" OFF)
OPTION(INF_BUILD "" OFF)
OPTION(SCP_LITE "" OFF)
OPTION(FS2_DEMO "Build demo" OFF)
OPTION(SPEECH "Build speech recognition (Windows only)" ON)
IF(WIN32)
	OPTION(JPEG_STATIC "Build statically with the included jpeg library" ON)
ELSEIF(WIN32)
	OPTION(JPEG_STATIC "Build statically with the included jpeg library" OFF)
ENDIF(WIN32)

IF(NOT WIN32 OR NOT HAVE_64_BIT)
	SET(SPEECH OFF)
ENDIF(NOT WIN32 OR NOT HAVE_64_BIT)

MESSAGE( STATUS "Build demo FS2_DEMO=${FS2_DEMO}" )
MESSAGE( STATUS "SCP_LITE=${SCP_LITE}" )
MESSAGE( STATUS "INF_BUILD=${INF_BUILD}" )
MESSAGE( STATUS "Turn off sound support NO_SOUND=${NO_SOUND}" )
MESSAGE( STATUS "Build speech recognition (32bit Windows only) SPEECH=${SPEECH}" )
MESSAGE( STATUS "Build statically with the included jpeg library JPEG_STATIC=${JPEG_STATIC}" )