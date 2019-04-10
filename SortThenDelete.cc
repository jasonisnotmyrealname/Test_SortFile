#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream> // std::cout
#include <string>
#include <algorithm> // std::sort, std::copy
#include <iterator> // std::ostream_iterator
#include <sstream> // std::istringstream
//#include <vector>
#include <cctype> // std::isdigit
#include <deque>
#include <string.h>
#include <unistd.h>


int get_sorted_filelist(const char * fpath,const char * ftype1,const char * ftype2,const char * ftype3,std::deque<std::string> &dq)
{
	int ret = -1;
	struct dirent **namelist;
    int n,i;
    
    n = scandir(fpath, &namelist, 0, versionsort);  //按升序扫描dir
    if (n >0 )
    {
		std::string filename;
		int dot_index = 0;
		int fn_len = 0;
        for(i =0 ; i < n; ++i)
        {
			filename = std::string(namelist[i]->d_name);
			dot_index = filename.find_last_of(".");
			fn_len = filename.length();
			std::string fullName = std::string(fpath) + filename;  //文件路径+文件名

			if (((fn_len - dot_index -1) == 3)) {   //缩小范围:后缀名长度必须为3

				std::string extension = filename.substr(filename.find_last_of(".") + 1);
				std::string filename_wo_ext = filename.erase(filename.find_last_of("."),4);
				
				if ((strcmp(extension.c_str(),ftype1) ==0) && \
				(!filename_wo_ext.empty() && filename_wo_ext.find_first_not_of("0123456789") == std::string::npos))   //缩小范围:后缀名ftype
				{
					dq.push_back(filename);
					ret = 0;
					
				}else{
					if (((strcmp(extension.c_str(),ftype1) !=0) && (strcmp(extension.c_str(),ftype2) !=0) && (strcmp(extension.c_str(),ftype3) !=0))
					|| filename_wo_ext.empty() || (filename_wo_ext.find_first_not_of("0123456789") != std::string::npos))
						ret = unlink(fullName.c_str());
						printf("unlink %s\n",fullName.c_str());
				}
			}else{
				if((strcmp(filename.c_str(),".") !=0)&&(strcmp(filename.c_str(),"..") !=0))
				{
					ret = unlink(fullName.c_str());
					printf("unlink %s\n",fullName.c_str());
				}
			}
        }
        free(namelist);
    }
	return ret;
}

int main(int argc, char * argv[])
{
	std::deque<std::string> str;
	get_sorted_filelist(argv[1],"jpg","IIQ","txt",str);
	std::copy(str.begin(), str.end(),std::ostream_iterator<std::string>(std::cout, "\n"));
}
