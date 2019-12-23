#include <maya/MFnPlugin.h>

#include "StringEquation.h"

MStatus initializePlugin(MObject pluginMObj) {
    MStatus status;
    MFnPlugin fn(pluginMObj);

    status = fn.setName("StringEquation");

    status = fn.registerNode(StringEquation::name, StringEquation::id, &StringEquation::creator, &StringEquation::initialize, MPxNode::kDependNode,
                             nullptr);

    return status;
}

MStatus uninitializePlugin(MObject pluginMObj) {
    MStatus status;
    MFnPlugin fn(pluginMObj);

    status = fn.deregisterNode(StringEquation::id);

    return status;
}
