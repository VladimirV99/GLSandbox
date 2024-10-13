set(ASSIMP_LIB_NAME "assimp")
set(ASSIMP_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/${ASSIMP_LIB_NAME}/include")

set(ASSIMP_BUILD_AMF_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_AC_IMPORTER        OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASE_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_IMPORTER    OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_BVH_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_COLLADA_IMPORTER   OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_DXF_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_CSM_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_HMP_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_IRRMESH_IMPORTER   OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_IQM_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_IRR_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_LWO_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_LWS_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_M3D_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MD2_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MD3_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MD5_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MDC_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MDL_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_NFF_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_NDO_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_OFF_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_OGRE_IMPORTER      OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_OPENGEX_IMPORTER   OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_PLY_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MS3D_IMPORTER      OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_COB_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER     OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_IFC_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_XGL_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_Q3BSP_IMPORTER     OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_RAW_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_SIB_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_SMD_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_STL_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TERRAGEN_IMPORTER  OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_3D_IMPORTER        OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_X_IMPORTER         OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_X3D_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER      OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_3MF_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_MMD_IMPORTER       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_NO_EXPORT                ON  CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS       OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TESTS              OFF CACHE INTERNAL "" FORCE)
add_subdirectory("${ASSIMP_LIB_NAME}")

set_target_properties("${ASSIMP_LIB_NAME}" PROPERTIES FOLDER "${LIB_DIR}")