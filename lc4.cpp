#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int get_kth(vector<int>& nums1, vector<int>& nums2,int k)
    {
        k--;

        int n = nums1.size(), m = nums2.size();

        
        
        int l = 0,r = n-1,ans = -1;

        while(l<r)
        {
            int mid = l+r>>1;

            int cnt = lower_bound(nums2.begin(),nums2.end(),nums1[mid]) - nums2.begin() + mid;
            if(cnt <= k)
            {
                ans = mid; l = mid+1;
            }
            else r = mid-1;
        }
        if(lower_bound(nums2.begin(),nums2.end(),nums1[ans]) - nums2.begin() + ans == k)
        {
            return nums1[ans];
        }

        l=0,r=m-1,ans=-1;
        while(l<r)
        {
            int mid = l+r>>1;

            int cnt = lower_bound(nums1.begin(),nums1.end(),nums2[mid]) - nums1.begin() + mid;
            if(cnt <= k)
            {
                ans = mid; l = mid+1;
            }
            else r = mid-1;
        }
        return nums2[ans];

    }


    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        
  
    }
};