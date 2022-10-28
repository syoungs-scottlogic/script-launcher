#ifndef STRING

#include <string>

#endif
#include <aws/core/Aws.h>

class AwsFunctions
{
public:
    Aws::String ListEc2Instances();
};