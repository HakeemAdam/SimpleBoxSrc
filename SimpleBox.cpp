#include <UT/UT_DSOVersion.h>
#include "SimpleBox.h"

#include <OP/OP_OperatorTable.h>
#include <OP/OP_Operator.h>
#include <OP/OP_AutoLockInputs.h>

#include <GU/GU_Detail.h>


#include <PRM/PRM_Include.h>




static PRM_Name names[]=
{
    PRM_Name("size", "Size"),
    PRM_Name("rotate", "Rotate"),
    PRM_Name("center", "Center"),
    PRM_Name("uniScale", "Uniform Scale"),
    PRM_Name("axis_division", "Axis Division")
};

static PRM_Default defaults[]=
{
    PRM_Default(1.0f),
    PRM_Default(1.0f),
    PRM_Default(1.0f),
    PRM_Default(0.0f),
    PRM_Default(0.0f),
    PRM_Default(0.0f)
};

static PRM_Template myTemplateList[] =
    {
    PRM_Template(PRM_XYZ, 3, &names[0], defaults),
    PRM_Template(PRM_XYZ, 3, &names[1], defaults+3),
    PRM_Template(PRM_XYZ, 3, &names[2], defaults+3),
    PRM_Template(PRM_FLT, 1, &names[3], &defaults[0]),
    PRM_Template(PRM_INT, 1, &names[4], &defaults[0]),
    PRM_Template()
    };

// size center rotate, uni scale, axis divisions vector3

void newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        "PG::SimpleBox",
        "PG::Simple Box",
        SimpleBox::myConstructor,
        myTemplateList,
        0,
        0,
        nullptr));
}
OP_Node* SimpleBox::myConstructor(OP_Network* net, const char* name, OP_Operator* op)
{
    return new SimpleBox(net, name, op);
}

SimpleBox::SimpleBox(OP_Network* net, const char* name, OP_Operator* op)
    : SOP_Node(net, name, op)
{
    mySopFlags.setManagesDataIDs(true);
}

SimpleBox::~SimpleBox()
{
}

OP_ERROR SimpleBox::cookMySop(OP_Context& context)
{

    OP_AutoLockInputs inputs(this);
    if(inputs.lock(context) >= UT_ERROR_ABORT)
        return  error();
    gdp->clear();
    float xmin = -evalFloat("size", 0, context.getTime())/2.0f;
    float xmax = evalFloat("size", 0, context.getTime())/2.0f;

    float ymin = -evalFloat("size", 1, context.getTime())/2.0f;
    float ymax = evalFloat("size", 1, context.getTime())/2.0f;

    float zmin = -evalFloat("size", 2, context.getTime())/2.0f;
    float zmax = evalFloat("size", 2, context.getTime())/2.0f;

    int div = evalInt("axis_division", 0, context.getTime());
    
    //gdp->cube(xmin, xmax, ymin, ymax, zmin, zmax, div, div, div, 0,1);
    gdp->meshCube(div,div,div,xmin, xmax,ymin,ymax,zmin,zmax,GEO_PATCH_QUADS,true);
    
    return error();
}
