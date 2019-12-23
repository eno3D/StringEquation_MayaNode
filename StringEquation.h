#ifndef SIMPLE_EQUATION_GUARD
#define SIMPLE_EQUATION_GUARD

#include <maya/MGlobal.h>
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>

static const int SIMPLE_EQUATION_ID = 0x001321c0;
static const char *SIMPLE_EQUATION_NAME = "StringEquation";

class StringEquation : public MPxNode {
public:
    static MTypeId id;
    static MString name;

    static MObject equation_mobj;
    static MObject a_mobj;
    static MObject b_mobj;
    static MObject c_mobj;
    static MObject d_mobj;
    static MObject e_mobj;
    static MObject output_mobj;

    StringEquation();

    ~StringEquation() override;

    static void *creator();

    static MStatus initialize();

    MStatus compute(const MPlug &plug, MDataBlock &dataBlock) override;
};

#endif