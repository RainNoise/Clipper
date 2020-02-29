#include "runtimeexception.h"

RuntimeException::RuntimeException(int code, const char* msg)
	: QException()
	, code(code)
	, message(msg)
{

}

QString RuntimeException::getMessage() const
{
	return message;
}

int RuntimeException::getCode() const
{
	return code;
}
