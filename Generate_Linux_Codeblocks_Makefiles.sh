BUILD_DIR=build

DIR=`pwd`
DEVLINE_DIR=/home/th0re/ShineDepot/Shine/MainLine

SHSDK_ROOT=${DEVLINE_DIR}/Build/Linux_CodeBlocks_Makefiles/cmake/lib/x86_64-linux-gnu/ShSDK

GENERATOR="CodeBlocks - Unix Makefiles"

mkdir ${BUILD_DIR}
cd ${BUILD_DIR}

	for CONFIG in Debug Release Master
	do
		mkdir ${CONFIG}
		cd ${CONFIG}

		for ARCHI in "x86" "x86_64"
		do
			mkdir ${ARCHI}
			cd ${ARCHI}
			cmake -G "${GENERATOR}" -DShSDK_ROOT=${SHSDK_ROOT} -DSHSDK_EDITOR_LIBRARIES="${DEVLINE_DIR}/Build/Linux_CodeBlocks_Makefiles/Tools/${CONFIG}/${ARCHI}/Libraries/Internal/ShCore/libShCore_Editor_Debug.so;${DEVLINE_DIR}/Build/Linux_CodeBlocks_Makefiles/Tools/${CONFIG}/${ARCHI}/Libraries/Internal/ShCompiler/libShCompiler_Editor_Debug.so;${DEVLINE_DIR}/Build/Linux_CodeBlocks_Makefiles/Tools/${CONFIG}/${ARCHI}/Libraries/Internal/ShSDK/libShSDK_Editor_Debug.so" -DSHINE_INTERNAL=1 -DSHINE_EDITOR_EXT_DIR="${DEVLINE_DIR}/Build/Linux_CodeBlocks_Makefiles/Compiled/Bin/${ARCHI}/Extensions" -DCMAKE_BUILD_TYPE="${CONFIG}" ${DIR}

			cd ..

		done

		cd ..

	done

cd ..

