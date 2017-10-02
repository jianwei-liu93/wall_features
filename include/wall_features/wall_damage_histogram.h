

#define PCL_NO_PRECOMPILE
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

struct WallDamageHistogram
{
  PCL_ADD_POINT4D;                  // preferred way of adding a XYZ+padding
  PCL_ADD_NORMAL4D; 				// This adds the member normal[3] which can also be accessed using the point (which is float[4])
  float angle_offset_avg; 			// Average offset in angle between local normal vectors of each neighbor point and the expected normal vector of the containing plane primitive definition
  float dist_offset_avg; 			// Average offset in position between each neighbor point and the containing plane primitive definition
  float	histogram[80];				// 40 points for distance deviation, 40 points for angle deviation - might change this later... 
  // Should the above be split into two histograms? Not sure what makes most sense computationally. For now, first half of the indices are distance-based, second half are angle-based 

  friend std::ostream& operator << (std::ostream& os, const WallDamageHistogram& p);

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW   // make sure our new allocators are aligned
} EIGEN_ALIGN16;                    // enforce SSE padding for correct memory alignment

POINT_CLOUD_REGISTER_POINT_STRUCT (WallDamageHistogram,           // here we assume a XYZ + "test" (as fields)
                                   (float, x, x)
                                   (float, y, y)
                                   (float, z, z)
                                   (float, angle_offset_avg, angle_offset_avg)
                                   (float, dist_offset_avg, dist_offset_avg)
                                   (float[80], histogram, histogram)

)
PCL_EXPORTS std::ostream& operator << (std::ostream& os, const WallDamageHistogram& p);