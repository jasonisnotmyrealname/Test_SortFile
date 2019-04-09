//#define _GNU_SOURCE
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

int main(int argc, char * argv[])
{
    struct dirent **namelist;
    int n,i;
    
    std::deque<std::string> str;  //deque有pop_front，而vector没有

    n = scandir(argv[1], &namelist, 0, versionsort);
    if (n < 0)
        perror("scandir");
    else
    {
        for(i =0 ; i < n; ++i)
        {
            str.push_back(namelist[i]->d_name);
        }
        str.pop_front();
        str.pop_front();
        std::copy(str.begin(), str.end(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
        free(namelist);
    }
    return 0;
}
