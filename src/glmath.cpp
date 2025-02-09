#include "../include/glmath.h"

// class vec2

glmath::vec2::vec2()
	: x(0.0f), y(0.0f) {};

glmath::vec2::vec2(float x)
	: x(x), y(x) {};

glmath::vec2::vec2(float x, float y)
	: x(x), y(y) {};

glmath::vec2::vec2(const vec2& copy)
	: x(copy.x), y(copy.y) {};

glmath::vec2& glmath::vec2::operator=(const glmath::vec2& copy) {
	this->x = copy.x;
	this->y = copy.y;
	return *this;
}

glmath::vec2 glmath::vec2::operator+(const vec2& rhs) const {
	return glmath::vec2(this->x + rhs.x, this->y + rhs.y);
}

glmath::vec2 glmath::vec2::operator-(const vec2& rhs) const{
	return glmath::vec2(this->x - rhs.x, this->y - rhs.y);
}

glmath::vec2 glmath::vec2::operator*(const vec2& rhs) const{
	return glmath::vec2(this->x * rhs.x, this->y * rhs.y);
}

float& glmath::vec2::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec2::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			throw std::out_of_range("Index out of range");
	}
}

// class vec3

glmath::vec3::vec3()
	: x(0.0f), y(0.0f), z(0.0f) {};

glmath::vec3::vec3(float x)
	: x(x), y(x), z(x) {};

glmath::vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z) {};

glmath::vec3::vec3(const vec3& copy)
	: x(copy.x), y(copy.y), z(copy.z) {};

glmath::vec3::vec3(const vec4& copy)
	: x(copy.x), y(copy.y), z(copy.z) {};

glmath::vec3& glmath::vec3::operator=(const glmath::vec3& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	return *this;
}

glmath::vec3& glmath::vec3::operator=(float copy) {
	this->x = copy;
	this->y = copy;
	this->z = copy;
	return *this;
}

glmath::vec3 glmath::vec3::operator+(const vec3& rhs) const {
	return glmath::vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

glmath::vec3 glmath::vec3::operator-(const vec3& rhs) const{
	return glmath::vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

glmath::vec3 glmath::vec3::operator*(const vec3& rhs) const{
	return glmath::vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}

float& glmath::vec3::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec3::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			throw std::out_of_range("Index out of range");
	}
}

// class vec4

glmath::vec4::vec4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}; 

glmath::vec4::vec4(float x)
	: x(x), y(x), z(x), w(x) {};

glmath::vec4::vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {};

glmath::vec4::vec4(const vec3& copy, float w)
	: x(copy.x), y(copy.y), z(copy.z), w(w) {};

glmath::vec4::vec4(const vec4& copy)
	: x(copy.x), y(copy.y), z(copy.z), w(copy.w) {};

glmath::vec4& glmath::vec4::operator=(const glmath::vec4& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
	return *this;
}

glmath::vec4 glmath::vec4::operator+(const vec4& rhs) const {
	return glmath::vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
}

glmath::vec4 glmath::vec4::operator-(const vec4& rhs) const {
	return glmath::vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
}

glmath::vec4 glmath::vec4::operator*(const vec4& rhs) const {
	return glmath::vec4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w);
}

float& glmath::vec4::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec4::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			throw std::out_of_range("Index out of range");
	}
}


// class mat4

glmath::mat4::mat4()
	: data{} {};

glmath::mat4::mat4(float x)
	: data{glmath::vec4(x, 0.0f, 0.0f, 0.0f), glmath::vec4(0.0f, x, 0.0f, 0.0f),
		glmath::vec4(0.0f, 0.0f, x, 0.0f), glmath::vec4(0.0f, 0.0f, 0.0f, x)} {};

glmath::mat4::mat4(const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4)
	: data{c1, c2, c3, c4} {};

glmath::mat4::mat4(const glmath::mat4& copy) {
	for (int i = 0; i < 4; i++) {
		(*this)[i] = copy[i];
	}
}

glmath::mat4& glmath::mat4::operator=(const mat4& copy) {
	for (int i = 0; i < 4; i++) {
		(*this)[i] = copy[i];
	}
	return *this;
}

glmath::mat4 glmath::mat4::operator+(const mat4& rhs) const {
	return glmath::mat4(glmath::vec4((*this)[0] + rhs[0]),
						glmath::vec4((*this)[1] + rhs[1]),
						glmath::vec4((*this)[2] + rhs[2]),
						glmath::vec4((*this)[3] + rhs[3]));
}

glmath::mat4 glmath::mat4::operator-(const mat4& rhs) const {
	return glmath::mat4(glmath::vec4((*this)[0] - rhs[0]),
						glmath::vec4((*this)[1] - rhs[1]),
						glmath::vec4((*this)[2] - rhs[2]),
						glmath::vec4((*this)[3] - rhs[3]));
}

glmath::mat4 glmath::mat4::operator*(const mat4& rhs) const {
	glmath::mat4 ret(0.0f);
	for (int i = 0; i < 4; i++) {
		ret[i] = (*this) * rhs[i];
	}
	return ret;
}

glmath::vec4& glmath::mat4::operator[](int idx) {
	if (0 <= idx && idx < 4) return this->data[idx];
	throw std::out_of_range("Index out of range");
}

glmath::vec4 glmath::mat4::operator[](int idx) const {
	if (0 <= idx && idx < 4) return this->data[idx];
	throw std::out_of_range("Index out of range");
}

// class quat

glmath::quat::quat()
	: x(0), y(0), z(0), w(1) {};

glmath::quat::quat(float x)
	: x(x), y(x), z(x), w(x) {};

glmath::quat::quat(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {};

glmath::quat::quat(const glmath::vec3& axis, float angle){
	glmath::vec3 normalAxis = glmath::normalize(axis);
	float halfAngle = angle / 2.0f;
	float s = sin(halfAngle);
	w = cos(halfAngle);
	x = normalAxis.x * s;
	y = normalAxis.y * s;
	z = normalAxis.z * s;
}

glmath::quat::quat(const vec3& eulerAngle) {
	glmath::quat xQuat(glmath::vec3(1.0f, 0.0f, 0.0f), glmath::radians(eulerAngle.x));
	glmath::quat yQuat(glmath::vec3(0.0f, 1.0f, 0.0f), glmath::radians(eulerAngle.y));
	glmath::quat zQuat(glmath::vec3(0.0f, 0.0f, 1.0f), glmath::radians(eulerAngle.z));
	glmath::quat mulQuat = xQuat * yQuat * zQuat;

	x = mulQuat.x;
	y = mulQuat.y;
	z = mulQuat.z;
	w = mulQuat.w;
}

glmath::quat glmath::quat::operator*(const quat& rhs) const {
	return quat (
		rhs.w * x + rhs.x * w + rhs.y * z - rhs.z * y,
		rhs.w * y - rhs.x * z + rhs.y * w + rhs.z * x,
		rhs.w * z + rhs.x * y - rhs.y * x + rhs.z * w,
		rhs.w * w - rhs.x * x - rhs.y * y - rhs.z * z
    );
}

// non-member operator function

glmath::vec2 glmath::operator*(float scalar, const glmath::vec2& vector) {
	return glmath::vec2(scalar * vector.x, scalar * vector.y);
}

glmath::vec2 glmath::operator*(const glmath::vec2& vector, float scalar) {
	return glmath::vec2(scalar * vector.x, scalar * vector.y);
}


glmath::vec3 glmath::operator*(float scalar, const glmath::vec3& vector) {
	return glmath::vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

glmath::vec3 glmath::operator*(const glmath::vec3& vector, float scalar) {
	return glmath::vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}


glmath::vec4 glmath::operator*(float scalar, const glmath::vec4& vector) {
	return glmath::vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
}

glmath::vec4 glmath::operator*(const glmath::vec4& vector, float scalar) {
	return glmath::vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
}

glmath::vec4 glmath::operator*(const glmath::mat4& matrix, const glmath::vec4& vector) {
	glmath::vec4 ret(0.0f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret[i] += matrix[j][i] * vector[j];
		}
	}
	return ret;
}

glmath::mat4 glmath::operator*(float scalar, const glmath::mat4& matrix) {
	return glmath::mat4({scalar * matrix[0], scalar * matrix[1], scalar * matrix[2], scalar * matrix[3]});
}

glmath::mat4 glmath::operator*(const glmath::mat4& matrix, float scalar) {
	return glmath::mat4({scalar * matrix[0], scalar * matrix[1], scalar * matrix[2], scalar * matrix[3]});
}

// non-member function

float* glmath::value_ptr(vec2& vector) {
	return &vector[0];
}

float* glmath::value_ptr(vec3& vector) {
	return &vector[0];
}

float* glmath::value_ptr(vec4& vector) {
	return &vector[0];
}

float* glmath::value_ptr(mat4& matrix) {
	return &matrix[0][0];
}

float glmath::dot(const glmath::vec2& vector1, const glmath::vec2& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 2; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

float glmath::dot(const glmath::vec3& vector1, const glmath::vec3& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 3; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

float glmath::dot(const glmath::vec4& vector1, const glmath::vec4& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 4; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

glmath::vec3 glmath::cross(const glmath::vec3& vector1, const glmath::vec3& vector2) {
	return glmath::vec3(vector1.y * vector2.z - vector1.z * vector2.y,
						vector1.z * vector2.x - vector1.x * vector2.z,
						vector1.x * vector2.y - vector1.y * vector2.x);
}

float glmath::length(const glmath::vec2& vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float glmath::length(const glmath::vec3& vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

glmath::vec2 glmath::normalize(const glmath::vec2& vector) {
	float magnitude = 0;
	for (int i = 0; i < 2; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec2(vector.x / magnitude, vector.y / magnitude);
}

glmath::vec3 glmath::normalize(const glmath::vec3& vector) {
	float magnitude = 0;
	for (int i = 0; i < 3; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec3(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude);
}

glmath::vec4 glmath::normalize(const glmath::vec4& vector) {
	float magnitude = 0;
	for (int i = 0; i < 4; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec4(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude, vector.w / magnitude);
}

float glmath::radians(float degree) {
	return degree * (3.14159f / 180.0f);
}

glmath::mat4 glmath::inverse(const glmath::mat4& matrix) {
	float coef00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
	float coef02 = matrix[1][2] * matrix[3][3] - matrix[3][2] * matrix[1][3];
	float coef03 = matrix[1][2] * matrix[2][3] - matrix[2][2] * matrix[1][3];

	float coef04 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];
	float coef06 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
	float coef07 = matrix[1][1] * matrix[2][3] - matrix[2][1] * matrix[1][3];

	float coef08 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];
	float coef10 = matrix[1][1] * matrix[3][2] - matrix[3][1] * matrix[1][2];
	float coef11 = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];

	float coef12 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];
	float coef14 = matrix[1][0] * matrix[3][3] - matrix[3][0] * matrix[1][3];
	float coef15 = matrix[1][0] * matrix[2][3] - matrix[2][0] * matrix[1][3];

	float coef16 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];
	float coef18 = matrix[1][0] * matrix[3][2] - matrix[3][0] * matrix[1][2];
	float coef19 = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];

	float coef20 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];
	float coef22 = matrix[1][0] * matrix[3][1] - matrix[3][0] * matrix[1][1];
	float coef23 = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];


	glmath::vec4 fac0(coef00, coef00, coef02, coef03);
	glmath::vec4 fac1(coef04, coef04, coef06, coef07);
	glmath::vec4 fac2(coef08, coef08, coef10, coef11);
	glmath::vec4 fac3(coef12, coef12, coef14, coef15);
	glmath::vec4 fac4(coef16, coef16, coef18, coef19);
	glmath::vec4 fac5(coef20, coef20, coef22, coef23);

	glmath::vec4 vec0(matrix[1][0], matrix[0][0], matrix[0][0], matrix[0][0]);
	glmath::vec4 vec1(matrix[1][1], matrix[0][1], matrix[0][1], matrix[0][1]);
	glmath::vec4 vec2(matrix[1][2], matrix[0][2], matrix[0][2], matrix[0][2]);
	glmath::vec4 vec3(matrix[1][3], matrix[0][3], matrix[0][3], matrix[0][3]);

	glmath::vec4 inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
	glmath::vec4 inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
	glmath::vec4 inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
	glmath::vec4 inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

	glmath::vec4 signA(+1, -1, +1, -1);
	glmath::vec4 signB(-1, +1, -1, +1);
	glmath::mat4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

	glmath::vec4 row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

	glmath::vec4 dot0(matrix[0] * row0);
	float det = (dot0.x + dot0.y) + (dot0.z + dot0.w);

	float oneOverDeterminant = 1.0f / det;

	return inverse * oneOverDeterminant;
}


glmath::mat4 glmath::scale(const glmath::mat4& matrix, const glmath::vec3& vector) {
	glmath::mat4 scaleMatrix(glmath::vec4(vector.x, 0.0f, 0.0f, 0.0f),
							glmath::vec4(0.0f, vector.y, 0.0f, 0.0f),
							glmath::vec4(0.0f, 0.0f, vector.z, 0.0f),
							glmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	return matrix * scaleMatrix;
}

glmath::mat4 glmath::translate(const glmath::mat4& matrix, const glmath::vec3& vector) {
	glmath::mat4 translateMatrix(glmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
								glmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),	
								glmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
								glmath::vec4(vector.x, vector.y, vector.z, 1.0f));
	return matrix * translateMatrix;
}

glmath::mat4 glmath::rotate(const glmath::mat4& matrix, float theta, const glmath::vec3& vector) {
	glmath::vec3 a = glmath::normalize(vector);
	glmath::mat4 rotateMatrix(glmath::vec4(cos(theta) + (1 - cos(theta)) * a.x * a.x,
											(1 - cos(theta)) * a.y * a.x + sin(theta) * a.z,
											(1 - cos(theta)) * a.z * a.x - sin(theta) * a.y,
											0.0f),
								glmath::vec4((1 - cos(theta)) * a.x * a.y - sin(theta) * a.z,
											cos(theta) + (1 - cos(theta)) * a.y * a.y,
											(1 - cos(theta)) * a.z * a.y + sin(theta) * a.x,
											0.0f),	
								glmath::vec4((1 - cos(theta)) * a.x * a.z + sin(theta) * a.y,
											(1 - cos(theta)) * a.y * a.z - sin(theta) * a.x,
											cos(theta) + (1 - cos(theta)) * a.z * a.z,
											0.0f),
								glmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));	
	return matrix * rotateMatrix;
}

glmath::mat4 glmath::perspective(float fovy, float aspect, float zNear, float zFar) {
	return glmath::mat4(glmath::vec4(1 / (aspect * tan(fovy / 2)), 0.0f, 0.0f, 0.0f),
						glmath::vec4(0.0f, 1 / tan(fovy / 2), 0.0f, 0.0f),
						glmath::vec4(0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), -1.0f),
						glmath::vec4(0.0f, 0.0f, (2 * zFar * zNear) / (zNear - zFar), 0.0f));
}

glmath::mat4 glmath::lookAt(const glmath::vec3& cameraPos, const glmath::vec3& cameraTarget, const glmath::vec3& cameraUp) {
	glmath::vec3 cameraZ = glmath::normalize(cameraPos - cameraTarget);
	glmath::vec3 cameraX = glmath::normalize(glmath::cross(cameraUp, cameraZ));
	glmath::vec3 cameraY = glmath::normalize(glmath::cross(cameraZ, cameraX));
	glmath::mat4 matrix(glmath::vec4(cameraX.x, cameraX.y, cameraX.z, 0.0f),
						glmath::vec4(cameraY.x, cameraY.y, cameraY.z, 0.0f),
						glmath::vec4(cameraZ.x, cameraZ.y, cameraZ.z, 0.0f),
						glmath::vec4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f));
	return glmath::inverse(matrix);
}

glmath::mat4 glmath::mat4_cast(const glmath::quat& quat) {
	glmath::mat4 rotate(1.0f);

	rotate[0][0] = 1.0f - 2.0f * quat.y * quat.y - 2.0f * quat.z * quat.z;
	rotate[1][0] = 2.0f * quat.x * quat.y - 2.0f * quat.w * quat.z;
	rotate[2][0] = 2.0f * quat.x * quat.z + 2.0f * quat.w * quat.y;

	rotate[0][1] = 2.0f * quat.x * quat.y + 2.0f * quat.w * quat.z;
	rotate[1][1] = 1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.z * quat.z;
	rotate[2][1] = 2.0f * quat.y * quat.z - 2.0f * quat.w * quat.x;

	rotate[0][2] = 2.0f * quat.x * quat.z - 2.0f * quat.w * quat.y;
	rotate[1][2] = 2.0f * quat.y * quat.z + 2.0f * quat.w * quat.x;
	rotate[2][2] = 1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.y * quat.y;

	return rotate;
}
