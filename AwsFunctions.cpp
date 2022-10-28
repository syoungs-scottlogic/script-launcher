#include "AwsFunctions.h"
#include <aws/ec2/EC2Client.h>
#include <aws/ec2/model/DescribeInstancesRequest.h>
#include <aws/ec2/model/DescribeInstancesResponse.h>
#include <iomanip>
#include <iostream>

Aws::String AwsFunctions::ListEc2Instances()
{
        Aws::EC2::EC2Client ec2;
        Aws::EC2::Model::DescribeInstancesRequest request;
        bool header = false;
        bool done = false;
        while (!done)
        {
            auto outcome = ec2.DescribeInstances(request);
            if (outcome.IsSuccess())
            {
                const auto &reservations =
                    outcome.GetResult().GetReservations();

                for (const auto &reservation : reservations)
                {
                    const auto &instances = reservation.GetInstances();
                    for (const auto &instance : instances)
                    {
                        Aws::String instanceStateString =
                            Aws::EC2::Model::InstanceStateNameMapper::GetNameForInstanceStateName(
                                instance.GetState().GetName());

                        Aws::String type_string =
                            Aws::EC2::Model::InstanceTypeMapper::GetNameForInstanceType(
                                instance.GetInstanceType());

                        Aws::String monitor_str =
                            Aws::EC2::Model::MonitoringStateMapper::GetNameForMonitoringState(
                                instance.GetMonitoring().GetState());
                        Aws::String name = "Unknown";

                        const auto &tags = instance.GetTags();
                        auto nameIter = std::find_if(tags.cbegin(), tags.cend(),
                            [](const Aws::EC2::Model::Tag &tag)
                        {
                            return tag.GetKey() == "Name";
                        });
                        if (nameIter != tags.cend())
                        {
                            name = nameIter->GetValue();
                        }
                        return name;
                    }
                }

                if (outcome.GetResult().GetNextToken().size() > 0)
                {
                    request.SetNextToken(outcome.GetResult().GetNextToken());
                }
                else
                {
                    done = true;
                }
            }
            else
            {   
                Aws::String returnString{"Failed to describe ec2 instances"};
                return returnString;
            }
        }
        Aws::String final{"finished block"};
    return final;
}