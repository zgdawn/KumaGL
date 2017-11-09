﻿// 继承自xgf::Error的异常类,由各调用模块抛出
#include "kgl_lib_pch.h"
#include "kgl_error.h"
#include "kgl_string_convertor.h"
#include "kgl_message_box.h"

namespace kgl
{
    Error::Error(const std::wstring& message): 
        title_(L"KGL Exception"), type_(EXCEPTION_MESSAGE), message_(message)
    {}

    Error::Error(const std::wstring& message, const char* file, uint32_t line):
        title_(L"KGL Exception"), type_(EXCEPTION_REGULAR), message_(message),
        file_(file), line_(line) 
    {}

    Error::Error(const std::vector<GLenum>& error_code_array, const std::vector<std::string>& error_desc_array, const char* file, uint32_t line) :
        title_(L"KGL Exception"), type_(EXCEPTION_OPENGL),
        file_(file), line_(line)
    {
        std::wstring file_name;
        std::wstring error_desc;
        StringConvertor::ANSItoUTF16LE(file_.c_str(), file_name);
        std::wstringstream wss;
        wss << message_ << L"\n" << file_name << L"\nLine " << line_;

        for (std::size_t i = 0; i < error_code_array.size(); ++i)
        {
            
            StringConvertor::ANSItoUTF16LE(error_desc_array.at(i).c_str(), error_desc);
            wss << L"\nOpenGL Error Code: " << error_code_array.at(i);
            wss << L"\nOpengGL Error Desc: " << error_desc;
            wss << L"\n====================================================";
        }

        message_ = wss.str();
    }

    std::wstring Error::AssembleOutput() const
    {
        switch(type_) 
        {
        case EXCEPTION_REGULAR:
            {
                std::wstring file_name;
                StringConvertor::ANSItoUTF16LE(file_.c_str(),file_name);
                std::wstringstream wss;
                wss<<message_<<L"\n"<<file_name<<L"\nLine "<<line_;
                return wss.str();
            }
        case EXCEPTION_MESSAGE:
        case EXCEPTION_OPENGL:
            return message_;
        default:
            break;
        }

        return std::wstring(L"");
    }

    void Error::Prompt() const 
    {
        std::wstring output = this->AssembleOutput() + L"\nQuit Program?";
		MessageBox(output, title_);
    }

    void Error::Notify() const 
    {
#if defined(WIN32) || defined(_WIN32)
        ::ShowCursor(true);
#endif
        MessageBox(AssembleOutput(),title_);
    }


    bool Error::GetGLErrorDesc(std::vector<std::string>& error_desc_array, std::vector<GLenum>& error_code_array)
    {
        error_desc_array.clear();
        error_code_array.clear();
        GLenum error_code = GL_NO_ERROR;
        bool has_error = false;
        
        while ((error_code = glGetError()) != GL_NO_ERROR)
        {
            switch (error_code)
            {
            case GL_INVALID_ENUM:
                error_desc_array.push_back("INVALID_ENUM");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            case GL_INVALID_VALUE:
                error_desc_array.push_back("INVALID_VALUE");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            case GL_INVALID_OPERATION:
                error_desc_array.push_back("INVALID_OPERATION");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            case GL_STACK_OVERFLOW:
                error_desc_array.push_back("STACK_OVERFLOW");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            case GL_STACK_UNDERFLOW:
                error_desc_array.push_back("STACK_UNDERFLOW");
                error_code_array.push_back(error_code);
                break;
            case GL_OUT_OF_MEMORY:
                error_desc_array.push_back("OUT_OF_MEMORY");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_desc_array.push_back("INVALID_FRAMEBUFFER_OPERATION");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            default:
                error_desc_array.push_back("UNKNOWN_GL_ERROR");
                error_code_array.push_back(error_code);
                has_error = true;
                break;
            }
        }
        
        return has_error;
    }
}
