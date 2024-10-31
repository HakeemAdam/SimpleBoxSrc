#ifndef __SIMPLE__BOX_H__
#define __SIMPLE__BOX_H__

#include <SOP/SOP_Node.h>

class SimpleBox : public SOP_Node
{

public:
    static OP_Node *myConstructor(OP_Network *net, const char *name, OP_Operator* op);
    static const PRM_Template* myTemplateList;

protected:
    SimpleBox(OP_Network *net, const char *name, OP_Operator* op);
    virtual ~SimpleBox();

    virtual OP_ERROR cookMySop(OP_Context &context);

private:
    void computeUVsAndNormals(GU_Detail *gdp);
};


#endif