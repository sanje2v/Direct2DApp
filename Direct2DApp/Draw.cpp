#include <array>
#include "MainWindow.h"


void MainWindow::ApplySettings()
{
	// User defined settings
	m_speed = 10;

	m_arrballs[0]->SetColor(ColorF::DarkBlue)
				 ->SetPos(0.0f, 0.0f)
				 ->SetRadius(20.0f)
				 ->SetIncrementX(INCREMENT)
				 ->SetIncrementY(INCREMENT);
				
	m_arrballs[1]->SetColor(ColorF::GreenYellow)
				 ->SetPos(150.0f, 150.0f)
				 ->SetRadius(50.0f)
				 ->SetIncrementX(INCREMENT)
				 ->SetIncrementY(INCREMENT);
}

void MainWindow::CreateDeviceDependentResources()
{

}

void MainWindow::CreateDeviceIndependentResources()
{
	
}

void MainWindow::Draw(D2D1_SIZE_F)
{
	m_d2d1rendertarget->Clear(WINDOW_BKCOLOR);

	for (size_t i = 0; i < m_arrballs.size(); i++)
	{
		Ball& ball = *m_arrballs[i];
		
		ball.Draw(m_d2d1rendertarget, Point2F(-25.0f, -25.0f), true);
	}
}

void MainWindow::AdvanceNextState(D2D1_SIZE_F canvassize)
{
	for (size_t i = 0; i < m_arrballs.size(); i++)
	{
		Ball& ball = *m_arrballs[i];
		float posX = ball.GetX();
		float posY = ball.GetY();
		float radius = ball.GetRadius();

		if (posX - radius - INCREMENT <= 0)
			ball.SetIncrementX(INCREMENT);
		else if (posX + radius + INCREMENT >= canvassize.width)
			ball.SetIncrementX(-INCREMENT);

		if (posY - radius - INCREMENT <= 0)
			ball.SetIncrementY(INCREMENT);
		else if (posY + radius + INCREMENT >= canvassize.height)
			ball.SetIncrementY(-INCREMENT);

		ball.Move();
	}
}