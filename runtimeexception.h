#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include<QException>

class RuntimeException : public QException
{
	int code;
	QString message;
public:
	RuntimeException(int code, const char* msg);

	int getCode() const;
	QString getMessage() const;
};

#endif // RUNTIMEEXCEPTION_H
