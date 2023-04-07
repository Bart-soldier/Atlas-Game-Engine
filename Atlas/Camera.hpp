#pragma once

class Camera {
	private:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;

	public:
		Camera(int posX, int posY, int width, int height);

		void centerOn(int x, int y, int width, int height);

		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
		void setPosX(int posX);
		void setPosY(int posY);
		void setWidth(int width);
		void setHeight(int height);
};

