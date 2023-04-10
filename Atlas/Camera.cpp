#include "Camera.hpp"

Camera::Camera(int posX, int posY, int width, int height) {
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;
}

void Camera::centerOn(int x, int y, int width, int height, int maxWidth, int maxHeight) {
	m_posX = (x + width / 2) - m_width / 2;
	m_posY = (y + height / 2) - m_height / 2;
	
	if (maxWidth != -1 && maxHeight != -1) {
		m_posX = (m_posX < 0) ? 0 : m_posX;
		m_posX = (maxWidth < m_posX + m_width) ? maxWidth - m_width : m_posX;

		m_posY = (m_posY < 0) ? 0 : m_posY;
		m_posY = (maxHeight < m_posY + m_height) ? maxHeight - m_height : m_posY;
	}
}

int Camera::getPosX() {
	return m_posX;
}

int Camera::getPosY() {
	return m_posY;
}

int Camera::getWidth() {
	return m_width;
}

int Camera::getHeight() {
	return m_height;
}

void Camera::setPosX(int posX) {
	m_posX = posX;
}

void Camera::setPosY(int posY) {
	m_posY = posY;
}

void Camera::setWidth(int width) {
	m_width = width;
}

void Camera::setHeight(int height) {
	m_height = height;
}