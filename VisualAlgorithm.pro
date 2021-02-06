QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AnimationService/animationservice.cpp \
    AnimationService/interpolatenccodethread.cpp \
    AnimationService/parsencthread.cpp \
    AnimationService/processncstepthread.cpp \
    AnimationService/timerrefreshthread.cpp \
    Application/main.cpp \
    DataStruct/doublelist.cpp \
    DataStruct/dynqueue.cpp \
    DataStruct/fixqueue.cpp \
    Drawing/drawing.cpp \
    Drawing/drawinggroup.cpp \
    FileGenerate/ModelFileGenerate/arraymodelfilegenerate.cpp \
    FileGenerate/ModelFileGenerate/modelfilegenerate.cpp \
    FileGenerate/NcFileGenerate/arrayncfilegenerate.cpp \
    FileGenerate/NcFileGenerate/ncfilegenerate.cpp \
    FileGenerate/filegenerate.cpp \
    FileParse/ModelFileParse/arraymodelfileparse.cpp \
    FileParse/ModelFileParse/modelfileparse.cpp \
    FileParse/NcFileParse/arrayncfileparse.cpp \
    FileParse/NcFileParse/ncfileparse.cpp \
    FileParse/fileparse.cpp \
    Functions/datastructfactory.cpp \
    Functions/pagemanager.cpp \
    Geometry/geometry.cpp \
    Geometry/geometryellipse.cpp \
    Geometry/geometrygroup.cpp \
    Geometry/geometryline.cpp \
    Geometry/geometrypoint.cpp \
    Geometry/geometrypolyline.cpp \
    Geometry/geometryrect.cpp \
    Geometry/geometrytext.cpp \
    Global/global.cpp \
    Matrix/matrix.cpp \
    Model/App/arraypart.cpp \
    Model/movablepart.cpp \
    Model/part.cpp \
    ModelManager/modelmanager.cpp \
    NcCode/nccode.cpp \
    NcCode/nccodecolor.cpp \
    NcCode/nccodecontrol.cpp \
    NcCode/nccodemove.cpp \
    NcCode/nccodetip.cpp \
    NcManager/ncmanager.cpp \
    NcShow/control.cpp \
    NcShow/image.cpp \
    NcShow/ncshow.cpp \
    NcShow/tip.cpp \
    NcStep/ncstep.cpp \
    NcStep/ncstepcolor.cpp \
    NcStep/ncstepcontrol.cpp \
    NcStep/ncstepmove.cpp \
    NcStep/ncsteptip.cpp \
    Parameter/ModelParameter/arraymodelparameter.cpp \
    Parameter/ModelParameter/modelparameter.cpp \
    Parameter/NcParameter/arrayncparameter.cpp \
    Parameter/NcParameter/ncparameter.cpp \
    Parameter/parameter.cpp \
    Struct/ellipse.cpp \
    Struct/line.cpp \
    Struct/point.cpp \
    Struct/polyline.cpp \
    Struct/rect.cpp \
    Sync/fixbufferfor1p1c.cpp \
    Transform/lineartransform.cpp \
    Transform/matrixtransform.cpp \
    Transform/rotatetransform.cpp \
    Transform/scaletransform.cpp \
    Transform/transform.cpp \
    Transform/transformgroup.cpp \
    Ui/Array/arraydeletewidget.cpp \
    Ui/Array/arrayinsertwidget.cpp \
    Ui/Array/arrayintroducewidget.cpp \
    Ui/Array/arrayorganizewidget.cpp \
    Ui/Array/arraysummarywidget.cpp \
    Ui/Array/arrayvaluevisitwidget.cpp \
    Ui/DataStruct/arraywidget.cpp \
    Ui/DataStruct/listwidget.cpp \
    Ui/Dialog/Array/createarraydialog.cpp \
    Ui/Drawing/arrayintroducedrawingwidget.cpp \
    Ui/Drawing/arrayorganizedrawingwidget.cpp \
    Ui/Drawing/arrayvaluedeletedrawingwidget.cpp \
    Ui/Drawing/arrayvalueinsertdrawingwidget.cpp \
    Ui/Drawing/arrayvaluevisitdrawingwidget.cpp \
    Ui/Drawing/listintroducedrawingwidget.cpp \
    Ui/Drawing/praticalarraydrawingwidget.cpp \
    Ui/List/listintroducewidget.cpp \
    Ui/PraticalArray/praticalarraylistwidget.cpp \
    Ui/PraticalArray/praticalarraywidget.cpp \
    Ui/datastructwidget.cpp \
    Ui/mainwindow.cpp \
    Vector/vector.cpp

HEADERS += \
    AnimationService/animationservice.h \
    AnimationService/header.h \
    AnimationService/interpolatenccodethread.h \
    AnimationService/lib.h \
    AnimationService/parsencthread.h \
    AnimationService/processncstepthread.h \
    AnimationService/timerrefreshthread.h \
    Application/header.h \
    Application/lib.h \
    Application/main.h \
    DataStruct/KeyAllocator.h \
    DataStruct/RedBlackTree.h \
    DataStruct/doublelist.h \
    DataStruct/dynarray.h \
    DataStruct/dynqueue.h \
    DataStruct/fixqueue.h \
    DataStruct/header.h \
    DataStruct/lib.h \
    Drawing/drawing.h \
    Drawing/drawinggroup.h \
    Drawing/header.h \
    Drawing/lib.h \
    FileGenerate/ModelFileGenerate/arraymodelfilegenerate.h \
    FileGenerate/ModelFileGenerate/modelfilegenerate.h \
    FileGenerate/NcFileGenerate/arrayncfilegenerate.h \
    FileGenerate/NcFileGenerate/ncfilegenerate.h \
    FileGenerate/filegenerate.h \
    FileGenerate/header.h \
    FileGenerate/lib.h \
    FileParse/ModelFileParse/arraymodelfileparse.h \
    FileParse/ModelFileParse/modelfileparse.h \
    FileParse/NcFileParse/arrayncfileparse.h \
    FileParse/NcFileParse/ncfileparse.h \
    FileParse/fileparse.h \
    FileParse/header.h \
    FileParse/lib.h \
    Functions/datastructfactory.h \
    Functions/header.h \
    Functions/lib.h \
    Functions/pagemanager.h \
    Geometry/geometry.h \
    Geometry/geometryellipse.h \
    Geometry/geometrygroup.h \
    Geometry/geometryline.h \
    Geometry/geometrypoint.h \
    Geometry/geometrypolyline.h \
    Geometry/geometryrect.h \
    Geometry/geometrytext.h \
    Geometry/header.h \
    Geometry/lib.h \
    Global/global.h \
    Global/header.h \
    Global/lib.h \
    Matrix/header.h \
    Matrix/lib.h \
    Matrix/matrix.h \
    Model/App/arraypart.h \
    Model/header.h \
    Model/lib.h \
    Model/movablepart.h \
    Model/part.h \
    ModelManager/header.h \
    ModelManager/lib.h \
    ModelManager/modelmanager.h \
    NcCode/header.h \
    NcCode/lib.h \
    NcCode/nccode.h \
    NcCode/nccodecolor.h \
    NcCode/nccodecontrol.h \
    NcCode/nccodemove.h \
    NcCode/nccodetip.h \
    NcManager/header.h \
    NcManager/lib.h \
    NcManager/ncmanager.h \
    NcShow/control.h \
    NcShow/header.h \
    NcShow/image.h \
    NcShow/lib.h \
    NcShow/ncshow.h \
    NcShow/tip.h \
    NcStep/header.h \
    NcStep/lib.h \
    NcStep/ncstep.h \
    NcStep/ncstepcolor.h \
    NcStep/ncstepcontrol.h \
    NcStep/ncstepmove.h \
    NcStep/ncsteptip.h \
    Parameter/ModelParameter/arraymodelparameter.h \
    Parameter/ModelParameter/modelparameter.h \
    Parameter/NcParameter/arrayncparameter.h \
    Parameter/NcParameter/ncparameter.h \
    Parameter/header.h \
    Parameter/lib.h \
    Parameter/parameter.h \
    Struct/ellipse.h \
    Struct/header.h \
    Struct/lib.h \
    Struct/line.h \
    Struct/point.h \
    Struct/polyline.h \
    Struct/rect.h \
    Sync/fixbufferfor1p1c.h \
    Sync/header.h \
    Sync/lib.h \
    Transform/header.h \
    Transform/lib.h \
    Transform/lineartransform.h \
    Transform/matrixtransform.h \
    Transform/rotatetransform.h \
    Transform/scaletransform.h \
    Transform/transform.h \
    Transform/transformgroup.h \
    Ui/Array/arraydeletewidget.h \
    Ui/Array/arrayinsertwidget.h \
    Ui/Array/arrayintroducewidget.h \
    Ui/Array/arrayorganizewidget.h \
    Ui/Array/arraysummarywidget.h \
    Ui/Array/arrayvaluevisitwidget.h \
    Ui/DataStruct/arraywidget.h \
    Ui/DataStruct/listwidget.h \
    Ui/Dialog/Array/createarraydialog.h \
    Ui/Drawing/arrayintroducedrawingwidget.h \
    Ui/Drawing/arrayorganizedrawingwidget.h \
    Ui/Drawing/arrayvaluedeletedrawingwidget.h \
    Ui/Drawing/arrayvalueinsertdrawingwidget.h \
    Ui/Drawing/arrayvaluevisitdrawingwidget.h \
    Ui/Drawing/listintroducedrawingwidget.h \
    Ui/Drawing/praticalarraydrawingwidget.h \
    Ui/List/listintroducewidget.h \
    Ui/PraticalArray/praticalarraylistwidget.h \
    Ui/PraticalArray/praticalarraywidget.h \
    Ui/datastructwidget.h \
    Ui/header.h \
    Ui/lib.h \
    Ui/mainwindow.h \
    Vector/header.h \
    Vector/lib.h \
    Vector/vector.h

FORMS += \
    Ui/Array/arraydeletewidget.ui \
    Ui/Array/arrayinsertwidget.ui \
    Ui/Array/arrayintroducewidget.ui \
    Ui/Array/arrayorganizewidget.ui \
    Ui/Array/arraysummarywidget.ui \
    Ui/Array/arrayvaluevisitwidget.ui \
    Ui/DataStruct/arraywidget.ui \
    Ui/DataStruct/listwidget.ui \
    Ui/Dialog/Array/createarraydialog.ui \
    Ui/List/listintroducewidget.ui \
    Ui/PraticalArray/praticalarraylistwidget.ui \
    Ui/PraticalArray/praticalarraywidget.ui \
    Ui/datastructwidget.ui \
    Ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

