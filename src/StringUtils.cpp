#include "StringUtils.h"
#include <iostream>

namespace StringUtils{

    std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
        auto cpy_str = str;
        int DStart = 0;
        int DEnd = str.size();
        int x = 0;
        

        if(start){
            DStart = start;

            if(start < 0){
                DStart = str.size() + start;
            }

            if(DStart > str.size()){
                return std::string();
            }
        }

        if(end){
            DEnd = end;

            if(DEnd < 0){
                DEnd = str.size() + end;
            }

            if((end < 0) && (DEnd > DStart)){
                x = str.size() - DStart;
                DEnd = x + end;
            }
        }

        return cpy_str.substr(DStart, DEnd);
    }

    std::string Capitalize(const std::string &str) noexcept{
        std::string cpy_str = "";
        cpy_str += toupper(str[0]);

        for(size_t i = 1; i < str.length(); i++)
        {
            cpy_str += tolower(str[i]);
        }

        return cpy_str;
    }

    std::string Upper(const std::string &str) noexcept{
        auto cpy_str = str;
        for(size_t i = 0; i < cpy_str.length(); i++)
        {
            cpy_str[i] = toupper(str[i]);
        }
        return cpy_str;
    }

    std::string Lower(const std::string &str) noexcept{
        auto cpy_str = str;
        for(size_t i = 0; i < cpy_str.length(); i++)
        {
            cpy_str[i] = tolower(str[i]);
        }
        return cpy_str;
    }

    std::string LStrip(const std::string &str) noexcept{

        auto cpy_str = str.begin();

        while(std::isspace(*cpy_str))
        {
            ++cpy_str;
        }

        return std::string(cpy_str, str.end());
    }

    std::string RStrip(const std::string &str) noexcept{
        auto cpy_str = str.rbegin();

        while(std::isspace(*cpy_str))
        {
            ++cpy_str;
        }

        return std::string(str.begin(), cpy_str.base());
    }

    std::string Strip(const std::string &str) noexcept{
        auto cpy_str = str;

        cpy_str = StringUtils::LStrip(cpy_str);
        cpy_str = StringUtils::RStrip(cpy_str);
        
        return cpy_str;
    }

    std::string Center(const std::string &str, int width, char fill) noexcept{
        std::string cpy_str;

        if(width < str.size()){
            return str;
        }
        
        int filler_size = width - str.size();

        int left = filler_size / 2;
        int right = filler_size - left;

        for(int i = 0 ; i < left ; i++){
            cpy_str += fill;
        }

        for(int j = 0; j < str.size(); j++){
            cpy_str += str[j];
        }

        for(int k =0; k < right; k++){
            cpy_str += fill;
        }

        return cpy_str;
    }

    std::string LJust(const std::string &str, int width, char fill) noexcept{
        std::string cpy_str;
        int filler_size = width - str.size();

        if(width < str.size()){
            return str;
        }

        for(size_t j = 0; j < str.length(); j++)
        {
            cpy_str += str[j];
        }

        for(size_t i = 0; i < filler_size; i++)
        {
            cpy_str += fill;
        }

        return cpy_str;
    }

    std::string RJust(const std::string &str, int width, char fill) noexcept{
        std::string cpy_str;
        int filler_size = width - str.size();

        if(width < str.size()){
            return str;
        }

        for(size_t i = 0; i < filler_size; i++)
        {
            cpy_str += fill;
        }

        for(size_t j = 0; j < str.length(); j++)
        {
            cpy_str += str[j];
        }

        return cpy_str;
    }

    std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
        auto cpy_str = str;

        for(size_t pos = cpy_str.find(old); pos != std::string::npos; pos = cpy_str.find(old, pos + rep.length()) )
        {
            cpy_str.replace(pos, old.length(), rep);
        }

        return cpy_str;
    }

    std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
        std::string cpy_str = str;
        std::string input;
        size_t total_space_pos = 0;
        std::vector<std::string> vectorStr = {};
        int pos = 0;
        int old_pos = 0;
        int skipStart = 0;

        if(splt.empty())
        {
            for(int k = 0; k < str.length(); k++){
                cpy_str = StringUtils::Replace(cpy_str, "\t", " ");
                cpy_str = StringUtils::Replace(cpy_str, "\n", " ");
                cpy_str = StringUtils::Replace(cpy_str, "  ", " ");
            }

            if(isspace(cpy_str[0])){
                input = "";
                vectorStr.push_back(input);             
                input.clear();
                skipStart = 1;
            }

            for(int i = skipStart; i < cpy_str.length(); i++)
            {
                pos++;

                if(isspace(cpy_str[i])){
                    input = cpy_str.substr(old_pos, pos - 1);
                    vectorStr.push_back(input);             
                    input.clear();
                    old_pos = old_pos + pos;
                    pos = 0;
                }
            }

            input = cpy_str.substr(old_pos, cpy_str.length());
            vectorStr.push_back(input);
            input.clear();
        }
        else
        {
            for(int k = 0; k < str.length(); k++){
                cpy_str = StringUtils::Replace(cpy_str, splt, " ");
                cpy_str = StringUtils::Replace(cpy_str, "\t", " ");
                cpy_str = StringUtils::Replace(cpy_str, "\n", " ");
                cpy_str = StringUtils::Replace(cpy_str, "  ", " ");
            }

            if(isspace(cpy_str[0])){
                input = "";
                vectorStr.push_back(input);             
                input.clear();
                skipStart = 1;
            }

            for(int i = skipStart; i < cpy_str.length(); i++)
            {
                pos++;
                if(isspace(cpy_str[i])){
                    input = cpy_str.substr(old_pos + 1, pos - 1);
                    vectorStr.push_back(input);             
                    input.clear();
                    old_pos = old_pos + pos;
                    pos = 0;
                }
            }

            input = cpy_str.substr(old_pos + 1, cpy_str.length());
            vectorStr.push_back(input);
            input.clear();
        }

        return vectorStr;
    }

    std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
        std::vector<std::string> cpy_vect = vect;
        std::string cpy_str = "";

        for(size_t i = 0; i < cpy_vect.size(); i++)
        {
            cpy_str += cpy_vect[i];

            if( i != cpy_vect.size()-1)
            {
                cpy_str += str;
            }
        }


        return cpy_str;
    }

    std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
        std::string cpy_str = "";
        int space_count;
        int tsize = 4;

        if(tabsize){
        tsize = tabsize;
        space_count = tsize;
        }

        if(tabsize != 0){
            for(size_t i = 0; i < str.length(); i++)
            {
                if(str.substr(i, 1) == "\t")
                {
                    for(size_t j = 0; j < space_count; j++)
                    {
                        cpy_str += " ";
                    }

                    space_count = tabsize;
                }
                else
                {
                    cpy_str += str[i];
                    space_count--;
                }

                if(space_count == 0){
                    space_count = tsize;
                }

            }
        }
        else{
            for(size_t i = 0; i < str.length(); i++)
            {
                if(str.substr(i, 1) == "\t")
                {
                    continue;
                }
                else
                {
                    cpy_str += str[i];
                    space_count--;
                }

            }        
        }

        return cpy_str;
    }

    int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
        std::string str1 = left;
        std::string str2 = right;
        int changes = 0;
        int length = str1.length();
        int end1 = str1.length();
        int end2 = str2.length();

        if(str1.length() < str2.length())
        {
            length = str2.length();
        }

        for(size_t i = 0; i < length / 2; i++)
        {
            if(ignorecase == true)
            {
                str1[i] = toupper(str1[i]);
                str2[i] = toupper(str2[i]);
            }

            if(str1[i] != str2[i])
            {
                changes += 1;
            }
        }

        for(size_t j = length; j > length / 2; j--)
        {
            if(ignorecase == true)
            {
                str1[j] = toupper(str1[end1]);
                str2[j] = toupper(str2[end2]);
            }
            
            if(str1[end1] != str2[end2])
            {
                changes += 1;
            }

            end1--;
            end2--;
        }

        return changes;
    }

};