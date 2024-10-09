#ifndef BUFFER_H
# define BUFFER_H

# include "humanGL.h"

class Buffer {
public:
	static std::shared_ptr<Buffer> create(GLenum type, GLsizeiptr size, const void* data, GLenum usage);
	~Buffer();

private:
	Buffer() {};
	void genBuffer(GLenum type, GLsizeiptr size, const void* data, GLenum usage);

	uint32_t m_buffer{0};
};

#endif