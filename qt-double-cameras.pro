QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia multimediawidgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    camera_window.cpp

HEADERS += \
    arcsoft/inc/amcomdef.h \
    arcsoft/inc/asvloffscreen.h \
    arcsoft/inc/free/arcsoft_face_sdk.h \
    arcsoft/inc/merror.h \
    arcsoft/opencv/include/opencv/cv.h \
    arcsoft/opencv/include/opencv/cv.hpp \
    arcsoft/opencv/include/opencv/cvaux.h \
    arcsoft/opencv/include/opencv/cvaux.hpp \
    arcsoft/opencv/include/opencv/cvwimage.h \
    arcsoft/opencv/include/opencv/cxcore.h \
    arcsoft/opencv/include/opencv/cxcore.hpp \
    arcsoft/opencv/include/opencv/cxeigen.hpp \
    arcsoft/opencv/include/opencv/cxmisc.h \
    arcsoft/opencv/include/opencv/highgui.h \
    arcsoft/opencv/include/opencv/ml.h \
    arcsoft/opencv/include/opencv2/calib3d/calib3d.hpp \
    arcsoft/opencv/include/opencv2/contrib/contrib.hpp \
    arcsoft/opencv/include/opencv2/contrib/detection_based_tracker.hpp \
    arcsoft/opencv/include/opencv2/contrib/hybridtracker.hpp \
    arcsoft/opencv/include/opencv2/contrib/openfabmap.hpp \
    arcsoft/opencv/include/opencv2/contrib/retina.hpp \
    arcsoft/opencv/include/opencv2/core/affine.hpp \
    arcsoft/opencv/include/opencv2/core/core.hpp \
    arcsoft/opencv/include/opencv2/core/core_c.h \
    arcsoft/opencv/include/opencv2/core/cuda_devptrs.hpp \
    arcsoft/opencv/include/opencv2/core/devmem2d.hpp \
    arcsoft/opencv/include/opencv2/core/eigen.hpp \
    arcsoft/opencv/include/opencv2/core/gpumat.hpp \
    arcsoft/opencv/include/opencv2/core/internal.hpp \
    arcsoft/opencv/include/opencv2/core/mat.hpp \
    arcsoft/opencv/include/opencv2/core/opengl_interop.hpp \
    arcsoft/opencv/include/opencv2/core/opengl_interop_deprecated.hpp \
    arcsoft/opencv/include/opencv2/core/operations.hpp \
    arcsoft/opencv/include/opencv2/core/types_c.h \
    arcsoft/opencv/include/opencv2/core/version.hpp \
    arcsoft/opencv/include/opencv2/core/wimage.hpp \
    arcsoft/opencv/include/opencv2/features2d/features2d.hpp \
    arcsoft/opencv/include/opencv2/flann/all_indices.h \
    arcsoft/opencv/include/opencv2/flann/allocator.h \
    arcsoft/opencv/include/opencv2/flann/any.h \
    arcsoft/opencv/include/opencv2/flann/autotuned_index.h \
    arcsoft/opencv/include/opencv2/flann/composite_index.h \
    arcsoft/opencv/include/opencv2/flann/config.h \
    arcsoft/opencv/include/opencv2/flann/defines.h \
    arcsoft/opencv/include/opencv2/flann/dist.h \
    arcsoft/opencv/include/opencv2/flann/dummy.h \
    arcsoft/opencv/include/opencv2/flann/dynamic_bitset.h \
    arcsoft/opencv/include/opencv2/flann/flann.hpp \
    arcsoft/opencv/include/opencv2/flann/flann_base.hpp \
    arcsoft/opencv/include/opencv2/flann/general.h \
    arcsoft/opencv/include/opencv2/flann/ground_truth.h \
    arcsoft/opencv/include/opencv2/flann/hdf5.h \
    arcsoft/opencv/include/opencv2/flann/heap.h \
    arcsoft/opencv/include/opencv2/flann/hierarchical_clustering_index.h \
    arcsoft/opencv/include/opencv2/flann/index_testing.h \
    arcsoft/opencv/include/opencv2/flann/kdtree_index.h \
    arcsoft/opencv/include/opencv2/flann/kdtree_single_index.h \
    arcsoft/opencv/include/opencv2/flann/kmeans_index.h \
    arcsoft/opencv/include/opencv2/flann/linear_index.h \
    arcsoft/opencv/include/opencv2/flann/logger.h \
    arcsoft/opencv/include/opencv2/flann/lsh_index.h \
    arcsoft/opencv/include/opencv2/flann/lsh_table.h \
    arcsoft/opencv/include/opencv2/flann/matrix.h \
    arcsoft/opencv/include/opencv2/flann/miniflann.hpp \
    arcsoft/opencv/include/opencv2/flann/nn_index.h \
    arcsoft/opencv/include/opencv2/flann/object_factory.h \
    arcsoft/opencv/include/opencv2/flann/params.h \
    arcsoft/opencv/include/opencv2/flann/random.h \
    arcsoft/opencv/include/opencv2/flann/result_set.h \
    arcsoft/opencv/include/opencv2/flann/sampling.h \
    arcsoft/opencv/include/opencv2/flann/saving.h \
    arcsoft/opencv/include/opencv2/flann/simplex_downhill.h \
    arcsoft/opencv/include/opencv2/flann/timer.h \
    arcsoft/opencv/include/opencv2/gpu/device/block.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/border_interpolate.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/color.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/common.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/datamov_utils.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/color_detail.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/reduce.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/reduce_key_val.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/transform_detail.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/type_traits_detail.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/detail/vec_distance_detail.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/dynamic_smem.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/emulation.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/filters.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/funcattrib.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/functional.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/limits.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/reduce.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/saturate_cast.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/scan.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/simd_functions.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/static_check.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/transform.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/type_traits.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/utility.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/vec_distance.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/vec_math.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/vec_traits.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/warp.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/warp_reduce.hpp \
    arcsoft/opencv/include/opencv2/gpu/device/warp_shuffle.hpp \
    arcsoft/opencv/include/opencv2/gpu/devmem2d.hpp \
    arcsoft/opencv/include/opencv2/gpu/gpu.hpp \
    arcsoft/opencv/include/opencv2/gpu/gpumat.hpp \
    arcsoft/opencv/include/opencv2/gpu/stream_accessor.hpp \
    arcsoft/opencv/include/opencv2/highgui/cap_ios.h \
    arcsoft/opencv/include/opencv2/highgui/highgui.hpp \
    arcsoft/opencv/include/opencv2/highgui/highgui_c.h \
    arcsoft/opencv/include/opencv2/highgui/ios.h \
    arcsoft/opencv/include/opencv2/imgproc/imgproc.hpp \
    arcsoft/opencv/include/opencv2/imgproc/imgproc_c.h \
    arcsoft/opencv/include/opencv2/imgproc/types_c.h \
    arcsoft/opencv/include/opencv2/legacy/blobtrack.hpp \
    arcsoft/opencv/include/opencv2/legacy/compat.hpp \
    arcsoft/opencv/include/opencv2/legacy/legacy.hpp \
    arcsoft/opencv/include/opencv2/legacy/streams.hpp \
    arcsoft/opencv/include/opencv2/ml/ml.hpp \
    arcsoft/opencv/include/opencv2/nonfree/features2d.hpp \
    arcsoft/opencv/include/opencv2/nonfree/gpu.hpp \
    arcsoft/opencv/include/opencv2/nonfree/nonfree.hpp \
    arcsoft/opencv/include/opencv2/nonfree/ocl.hpp \
    arcsoft/opencv/include/opencv2/objdetect/objdetect.hpp \
    arcsoft/opencv/include/opencv2/ocl/matrix_operations.hpp \
    arcsoft/opencv/include/opencv2/ocl/ocl.hpp \
    arcsoft/opencv/include/opencv2/opencv.hpp \
    arcsoft/opencv/include/opencv2/opencv_modules.hpp \
    arcsoft/opencv/include/opencv2/photo/photo.hpp \
    arcsoft/opencv/include/opencv2/photo/photo_c.h \
    arcsoft/opencv/include/opencv2/stitching/detail/autocalib.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/blenders.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/camera.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/exposure_compensate.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/matchers.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/motion_estimators.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/seam_finders.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/util.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/util_inl.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/warpers.hpp \
    arcsoft/opencv/include/opencv2/stitching/detail/warpers_inl.hpp \
    arcsoft/opencv/include/opencv2/stitching/stitcher.hpp \
    arcsoft/opencv/include/opencv2/stitching/warpers.hpp \
    arcsoft/opencv/include/opencv2/superres/optical_flow.hpp \
    arcsoft/opencv/include/opencv2/superres/superres.hpp \
    arcsoft/opencv/include/opencv2/ts/gpu_perf.hpp \
    arcsoft/opencv/include/opencv2/ts/gpu_test.hpp \
    arcsoft/opencv/include/opencv2/ts/ts.hpp \
    arcsoft/opencv/include/opencv2/ts/ts_gtest.h \
    arcsoft/opencv/include/opencv2/ts/ts_perf.hpp \
    arcsoft/opencv/include/opencv2/video/background_segm.hpp \
    arcsoft/opencv/include/opencv2/video/tracking.hpp \
    arcsoft/opencv/include/opencv2/video/video.hpp \
    arcsoft/opencv/include/opencv2/videostab/deblurring.hpp \
    arcsoft/opencv/include/opencv2/videostab/fast_marching.hpp \
    arcsoft/opencv/include/opencv2/videostab/fast_marching_inl.hpp \
    arcsoft/opencv/include/opencv2/videostab/frame_source.hpp \
    arcsoft/opencv/include/opencv2/videostab/global_motion.hpp \
    arcsoft/opencv/include/opencv2/videostab/inpainting.hpp \
    arcsoft/opencv/include/opencv2/videostab/log.hpp \
    arcsoft/opencv/include/opencv2/videostab/motion_stabilizing.hpp \
    arcsoft/opencv/include/opencv2/videostab/optical_flow.hpp \
    arcsoft/opencv/include/opencv2/videostab/stabilizer.hpp \
    arcsoft/opencv/include/opencv2/videostab/videostab.hpp \
    camera-interface.h \
    camera.h \
    camera_window.h \
    zxing/BarcodeFormat.h \
    zxing/BitHacks.h \
    zxing/ByteArray.h \
    zxing/DecodeHints.h \
    zxing/DecodeStatus.h \
    zxing/Flags.h \
    zxing/GTIN.h \
    zxing/ImageView.h \
    zxing/Point.h \
    zxing/Quadrilateral.h \
    zxing/ReadBarcode.h \
    zxing/Result.h \
    zxing/StructuredAppend.h \
    zxing/TextUtfEncoding.h \
    zxing/ZXContainerAlgorithms.h

FORMS += \
    camera_window.ui

TRANSLATIONS += \
    qt-double-cameras_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qt-double-cameras.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/x64/release/ -lZXing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/x64/debug/ -lZXing
else:unix: LIBS += -L$$PWD/libs/x64/ -lZXing -larcsoft_face_engine

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/x64/release/ -llibarcsoft_face_engine -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/x64/debug/ -llibarcsoft_face_engine -lopencv_core249d -lopencv_highgui249d -lopencv_imgproc249d
else:unix: LIBS += -L$$PWD/libs/x64/ -lZXing -larcsoft_face_engine




INCLUDEPATH += $$PWD/libs/x64
DEPENDPATH += $$PWD/libs/x64

INCLUDEPATH += $$PWD/zxing

INCLUDEPATH += $$PWD/arcsoft/inc
INCLUDEPATH += $$PWD/arcsoft/opencv/include
