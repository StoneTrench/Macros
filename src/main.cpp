#include <iostream>
#include <random>
#include "HTextWriter.cpp"
#include "HInputSim.cpp"
#include "HImage.cpp"
#include "HColorInspector.cpp"
#define CHANNELS_COUNT 10
#define INSPECTOR_COUNT 10

using namespace std;

// std::string *channels = new std::string[CHANNELS_COUNT]{
// 	"https://onlinestream.live/m1/videoplayer/5901-1",
// 	"https://onlinestream.live/m2-petofi-tv/videoplayer/5902-1",
// 	"https://onlinestream.live/stream/videoplayer/5931-1",
// 	"https://onlinestream.live/m4-sport/videoplayer/5903-1",
// 	"https://onlinestream.live/stream/videoplayer/5904-1",
// 	"https://onlinestream.live/duna/videoplayer/5905-1",
// 	"https://onlinestream.live/duna-world-m4-sport/videoplayer/5906-1",
// 	"https://onlinestream.live/mtva-idoszakos-kozvetitesek/videoplayer/5907-1",
// 	"https://onlinestream.live/max4/videoplayer/8714-1",
// 	"https://onlinestream.live/hir-tv/videoplayer/4740-1"};

double screenWidth_cm = 88;
double screenHeight_cm = 50;

// double videoScreenX_cm = 25;
// double videoScreenY_cm = 32;

// double videoScreenW_cm = 58;
// double videoScreenH_cm = 58;

// double searchBarX_cm = 12;
// double searchBarY_cm = 4.5;

double scrollIncrement_px = 42;

int backButtonTopY_px = 257;
int expandButtonRelativeBackButtonY_px = 278;

int browserOffset_px = 0;

int sleepTime = 500;	  // [ms]
int sameThreshold = 2000; // [ms]

// void Convert_cm_px(int &out_x, int &out_y, int in_x, int in_y, int screenWidth_px, int screenHeight_px)
// {
// 	out_x = in_x / screenWidth_cm * screenWidth_px;
// 	out_y = in_y / screenHeight_cm * screenHeight_px;
// }

void Refresh(HImage::Image &back_button_reference)
{
	// Center the mouse on the webpage
	int screenW_px;
	int screenH_px;
	HInputSim::GetScreenSize(screenW_px, screenH_px);
	HInputSim::SetMousePosition(screenW_px / 2, screenH_px / 2);

	// Refresh the webpage
	HInputSim::KeyClick(HInputSim::KEYCODES::BROWSER_REFRESH);

	// Wait for it to load
	HInputSim::SleepFor(1000);

	// Go to the top of the page
	HInputSim::KeyDown(HInputSim::KEYCODES::PAGE_UP);
	HInputSim::SleepFor(250);
	HInputSim::KeyUp(HInputSim::KEYCODES::PAGE_UP);

	// Scroll to where the back button is at the top most of the page
	HInputSim::MouseScrollY(backButtonTopY_px / scrollIncrement_px);

	// Take a screenshot
	// HImage::Image screen;
	// HImage::CaptureScreen(screen);

	// Find the back button on the page
	// int bestX, bestY, dummy2;
	// HImage::CompareImages(bestX, bestY, dummy2, screen, back_button_reference, 15, 2);
	// bestX += back_button_reference.width / 2;
	// bestY += expandButtonRelativeBackButtonY_px;

	// The expand button is relative to the back button, find and click it.
	// HInputSim::SetMousePosition(bestX / 2, bestY / 2);
	HInputSim::SleepFor(57);
	HInputSim::MouseClick(HInputSim::MOUSE_BUTTON::LEFT);
	HInputSim::SleepFor(900);
	HInputSim::MouseClick(HInputSim::MOUSE_BUTTON::LEFT);
	// HInputSim::SleepFor(57);
	HInputSim::MouseClick(HInputSim::MOUSE_BUTTON::LEFT);
}

std::random_device rd;
std::mt19937 gen(rd());
void GetRandomPosition(int &x, int &y)
{
	int screenX, screenY;
	HInputSim::GetScreenSize(screenX, screenY);
	std::uniform_int_distribution<> disX(0, screenX);
	std::uniform_int_distribution<> disY(0, screenY);
	x = disX(gen);
	y = disY(gen);
}

int main()
{
	printf("5 second timer started...\n");
	HInputSim::SleepFor(5000);

	printf("Loading reference...\n");
	HImage::Image ref_img;
	// HImage::ReadImage("./src/ref/BACK_BUTTON_REFERENCE.PNG", ref_img);
	HImage::ReadBase64("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", ref_img);

	sameThreshold /= sleepTime;

	printf("Creating color inspectors...\n");
	HColorInspector::ColorInspector *insps[INSPECTOR_COUNT];
	for (size_t i = 0; i < INSPECTOR_COUNT; i++)
	{
		int x, y;
		GetRandomPosition(x, y);
		insps[i] = new HColorInspector::ColorInspector(x, y, sameThreshold);
	}

	int failureCount = INSPECTOR_COUNT / 1.5;

	Refresh(ref_img);

	u_char state = 0;
	// 0 -> video is fine
	// 1 -> video paused fix
	// 2 -> checking if 1 fix worked
	// 3 -> video timeout fix

	printf("Starting update loop...\n");
	int inspFailCounter = 0;
	int inspStepCounter = 0;
	bool shouldShutdown = false;

	int screenCenterW_px;
	int screenCenterH_px;
	HInputSim::GetScreenSize(screenCenterW_px, screenCenterH_px);
	screenCenterW_px /= 2;
	screenCenterH_px /= 2;

	while (!shouldShutdown)
	{
		shouldShutdown = shouldShutdown || HInputSim::GetKey(HInputSim::KEYCODES::RIGHT_SHIFT);
		switch (state)
		{
		case 0:
			for (size_t i = 0; i < INSPECTOR_COUNT; i++)
			{
				if (insps[i]->Update())
					inspFailCounter++;
			}
			if (inspFailCounter > failureCount)
				state = 1;
			inspFailCounter = 0;
			break;
		case 1:
			printf("Video failed!\n");
			printf("Attempting to unpause it!\n");
			HInputSim::SetMousePosition(screenCenterW_px, screenCenterH_px);
			HInputSim::MouseClick(HInputSim::MOUSE_BUTTON::LEFT);
			state = 2;
			break;
		case 2:
			for (size_t i = 0; i < INSPECTOR_COUNT; i++)
			{
				if (insps[i]->Update())
					inspFailCounter++;
				if (insps[i]->stepCounter == insps[i]->sameThreshold)
					inspStepCounter++;
			}
			if (inspFailCounter > failureCount)
				state = 3;
			else if (inspStepCounter > failureCount)
			{
				state = 0;
				printf("Returning to default state...\n");
			}
			break;
		case 3:
			printf("Attempting to reload page!\n");
			Refresh(ref_img);
			state = 0;
			printf("Returning to default state...\n");
			break;
		default:
			break;
		}
		HInputSim::SleepFor(sleepTime);
	}
}