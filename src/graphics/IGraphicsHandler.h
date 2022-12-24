#pragma once

class IGraphicsHandler
{
protected:
	IGraphicsHandler() { }
	~IGraphicsHandler() { }
public:
	virtual unsigned int init() = 0;
	virtual void clear() = 0;
};