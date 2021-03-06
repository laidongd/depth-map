//
//  main.cpp
//  DfUSMC: Depth from Uncalibrated Small Motion Clip
//
//  Created by Hyowon Ha on 2016. 6. 11..
//  Copyright © 2016 Hyowon Ha. All rights reserved.
//

#include <iostream>
#include "DfUSMC.hpp"

int main(int argc, const char * argv[]) {
    char data_name[1024], video_format[1024], video_path[1024], result_path[1024];
    
    if (argc!=5) {
        printf("Usage: DfUSMC <data_name> <video_extension> <video_path> <result_path>\n");
        return -1;
    }
    else {
        sprintf(data_name, "%s", argv[1]);
        sprintf(video_format, "%s", argv[2]);
        sprintf(video_path, "%s", argv[3]);
        sprintf(result_path, "%s", argv[4]);        
    }
    
    DfUSMC dfusmc;
    
    // load small motion clip
    char fullpath[1024];
    sprintf(fullpath,"%s/%s.%s", video_path, data_name, video_format);
    dfusmc.LoadSmallMotionClip(fullpath);
    
    // (optional) save Reference image
    sprintf(fullpath,"%s/%s_ref.bmp",result_path, data_name);
    dfusmc.SaveReferenceImage(fullpath);
    
    // feature extraction and tracking
    dfusmc.FeatureExtractionAndTracking();
    
    // bundle adjustment
    dfusmc.BundleAdjustment();
    
    // (optional) save sparse reconstruction result.
    sprintf(fullpath,"%s/%s.ply",result_path, data_name);
    dfusmc.SavePointCloudPLY(fullpath);
    
    // image undistortion
    dfusmc.UndistortImages();
    
    // dense matching
    dfusmc.DenseMatching(0.5, 64, 3.0, 0.2);
    
    // (optional) save Winner-Takes-All depthmap result.
    sprintf(fullpath,"%s/%s_WTA.bmp",result_path, data_name);
    dfusmc.SaveDepthmapWTA(fullpath, true);
    
    // (optional) save filtered depthmap result.
    sprintf(fullpath,"%s/%s_Filtered.bmp",result_path, data_name);
    dfusmc.SaveDepthmapFiltered(fullpath, true);

    // (optional) save refined depthmap result.
    sprintf(fullpath,"%s/%s_Refined.bmp",result_path, data_name);
    dfusmc.SaveDepthmapRefined(fullpath, true);

    // waitKey(0);
    
    std::cout << "Done.\n";
    return 0;
}
