#include <system/vrEventReceiver.h>
#include <system/vrSystem.h>

bool VREventReceiver::OnEvent(const SEvent& event) {
	//	printf("Event occured!\n"); fflush(stdout);
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		//		printf("\nState of key %d is %d\n", event.KeyInput.Key, event.KeyInput.PressedDown); fflush(stdout);		
		//printf("\nESC key code is %d \n", FS_KEY_ESC); fflush(stdout);
		key[event.KeyInput.Key]
				= event.KeyInput.PressedDown;
		(event.KeyInput.PressedDown) ? key_pressed++
				: key_pressed--;
		//printf("\nState of SHIFT key is %d\n\n", event.KeyInput.Shift); fflush(stdout);
		key_shifts = event.KeyInput.Shift;

		VRSystem::getInstance()->getScreenManager().sendInputEvent(
				detectPlayerKey(event.KeyInput.Key),
				convertPlayerKey(event.KeyInput.Key),
				event.KeyInput.PressedDown, key_shifts);

		return true;
	}
	return false;
}

int VREventReceiver::detectPlayerKey(int key) {
	switch (key) {
	case VR_P1_KEY_X:
	case VR_P1_KEY_Z:
	case VR_P1_KEY_C:
	case VR_P1_KEY_V:
	case VR_P1_KEY_UP:
	case VR_P1_KEY_DOWN:
	case VR_P1_KEY_LEFT:
	case VR_P1_KEY_RIGHT:
	case VR_P1_KEY_ESC:
	case VR_P1_KEY_CREDIT:
	case VR_P1_KEY_START:
		return VR_PLAYER1;
		break;
	case VR_P2_KEY_X:
	case VR_P2_KEY_Z:
	case VR_P2_KEY_C:
	case VR_P2_KEY_V:
	case VR_P2_KEY_UP:
	case VR_P2_KEY_DOWN:
	case VR_P2_KEY_LEFT:
	case VR_P2_KEY_RIGHT:
	case VR_P2_KEY_ESC:
	case VR_P2_KEY_CREDIT:
	case VR_P2_KEY_START:
		return VR_PLAYER2;
		break;
	case VR_P3_KEY_X:
	case VR_P3_KEY_Z:
	case VR_P3_KEY_C:
	case VR_P3_KEY_V:
	case VR_P3_KEY_UP:
	case VR_P3_KEY_DOWN:
	case VR_P3_KEY_LEFT:
	case VR_P3_KEY_RIGHT:
	case VR_P3_KEY_ESC:
	case VR_P3_KEY_CREDIT:
	case VR_P3_KEY_START:
		return VR_PLAYER3;
		break;
	}
	return -1;
}

int VREventReceiver::convertPlayerKey(int key) {
	switch (key) {
	case VR_P1_KEY_X:
	case VR_P2_KEY_X:
	case VR_P3_KEY_X:
		return VR_KEY_X;
		break;
	case VR_P1_KEY_Z:
	case VR_P2_KEY_Z:
	case VR_P3_KEY_Z:
		return VR_KEY_Z;
		break;
	case VR_P1_KEY_C:
	case VR_P2_KEY_C:
	case VR_P3_KEY_C:
		return VR_KEY_C;
		break;
	case VR_P1_KEY_V:
	case VR_P2_KEY_V:
	case VR_P3_KEY_V:
		return VR_KEY_V;
		break;
	case VR_P1_KEY_UP:
	case VR_P2_KEY_UP:
	case VR_P3_KEY_UP:
		return VR_KEY_UP;
		break;
	case VR_P1_KEY_DOWN:
	case VR_P2_KEY_DOWN:
	case VR_P3_KEY_DOWN:
		return VR_KEY_DOWN;
		break;
	case VR_P1_KEY_LEFT:
	case VR_P2_KEY_LEFT:
	case VR_P3_KEY_LEFT:
		return VR_KEY_LEFT;
		break;
	case VR_P1_KEY_RIGHT:
	case VR_P2_KEY_RIGHT:
	case VR_P3_KEY_RIGHT:
		return VR_KEY_RIGHT;
		break;
	case VR_P1_KEY_ESC:
	case VR_P2_KEY_ESC:
	case VR_P3_KEY_ESC:
		return VR_KEY_ESC;
		break;
	case VR_P1_KEY_CREDIT:
	case VR_P2_KEY_CREDIT:
	case VR_P3_KEY_CREDIT:
		return VR_KEY_CREDIT;
		break;
	case VR_P1_KEY_START:
	case VR_P2_KEY_START:
	case VR_P3_KEY_START:
		return VR_KEY_START;
		break;
	}
	return -1;
}
