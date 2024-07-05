#include "Input.h"
#include<cassert>
#include<algorithm>

bool Input::GetCurrentInput(const std::string& input) const
{
	auto it = currentState_.find(input);
	if (it == currentState_.end())
	{
		return false;
	}
	return it->second;
}

bool Input::GetLastInput(const std::string& input) const
{
	auto it = lastState_.find(input);
	if (it == lastState_.end())
	{
		return false;
	}
	return it->second;
}

Input::Input()
{
	//���ӂ��Q�[���̖���(������)
	inputTable_["next"] = {
							{ InputType::keybord, KEY_INPUT_RETURN} ,
							{InputType::gamepad,PAD_INPUT_R } ,//pad��start
							{ InputType::mouse,MOUSE_INPUT_LEFT }
							};
	inputTable_["cancel"] = {
							{ InputType::keybord, KEY_INPUT_ESCAPE} 
							};


	inputTable_["pause"] = { 
							{InputType::keybord, KEY_INPUT_P},
							{ InputType::gamepad,PAD_INPUT_L } //pad��select
							};


	//�W�����v
	inputTable_["jump"] = {
							{ InputType::keybord, KEY_INPUT_Z} ,
							{InputType::gamepad,PAD_INPUT_B} //pad��A�@�v���X�e�́�
							};

	//hukku
	inputTable_["hook"] = {
							{ InputType::keybord, KEY_INPUT_X} ,
							{InputType::gamepad,PAD_INPUT_C} //�v���X�e�́~
							};
	//item
	inputTable_["item"] = {
							{ InputType::keybord, KEY_INPUT_V} ,
							{InputType::gamepad,PAD_INPUT_X} //�v���X�e�́~
							};

	//�X���C�f�B���O
	inputTable_["c"] = {
							{ InputType::keybord, KEY_INPUT_C} ,
							{InputType::gamepad,PAD_INPUT_A} //pad��A�@�v���X�e�́�

	};

	//��
	inputTable_["up"] = {
							{ InputType::keybord, KEY_INPUT_UP} ,
							{InputType::gamepad,PAD_INPUT_UP} ,//pad��A
	};

	//��
	inputTable_["down"] = {
							{ InputType::keybord, KEY_INPUT_DOWN} ,
							{InputType::gamepad,PAD_INPUT_DOWN} ,//pad��A
	};
	//�E
	inputTable_["right"] = {
							{ InputType::keybord, KEY_INPUT_RIGHT} ,
							{InputType::gamepad,PAD_INPUT_RIGHT} ,//pad��A
	};
	//��
	inputTable_["left"] = {
							{ InputType::keybord, KEY_INPUT_LEFT} ,
							{InputType::gamepad,PAD_INPUT_LEFT} ,//pad��A
	};
	//�L�[�R���t�B�O
	inputTable_["keyconfig"] = {
							{ InputType::keybord, KEY_INPUT_K} ,
	};

	LoadInputTable();

	tempTable_ = inputTable_;
	currentState_.clear();
	for (const auto& record: inputTable_)
	{
		currentState_[record.first] = false;
	}

	excludeOnCongigList_.reserve(5);
	excludeOnCongigList_.push_back("left");
	excludeOnCongigList_.push_back("right");
	excludeOnCongigList_.push_back("up");
	excludeOnCongigList_.push_back("down");
	excludeOnCongigList_.push_back("c");

}

void Input::Update(int padNum)
{
	
	//�n�[�h�̓��͎��̂̓`�F�b�N���܂�
	char keycode[256];
	GetHitKeyStateAll(keycode);//�L�[�{�[�h����
	auto a= 0x0000 + padNum;
	int padInfo = GetJoypadInputState(a);//�p�b�h�P�ԓ���
	auto padInfo2 = GetJoypadDirectInputState(a, &joyDInState_);
	int mouseInfo = GetMouseInput();//�}�E�X����

	lastState_ = currentState_;//�X�V�O�̏����L�^
	//���ׂĂ̓o�^�ς݂̓��͂��`�F�b�N����
	for (const auto& record : inputTable_)
	{
		bool pressed = false;
		for (const auto& inputInfo : record.second)
		{
			//���͎�ʂɂ�Ē��ו����Ⴄ
			switch (inputInfo.type)
			{
			case InputType::keybord:
				pressed = keycode[inputInfo.inputID];
				break;
			case InputType::gamepad:
				pressed = padInfo &inputInfo.inputID;
				break;
			case InputType::mouse:
				pressed = mouseInfo & inputInfo.inputID;
				break;
			}
			//�P�ł�������Ă����烋�[�v���~�܂�
			if (pressed)//�����厖
			{
				break;
			}
		}
		currentState_[record.first] = pressed;
	}
}

bool Input::IsTriggerd(const std::string& input) const
{

	return !GetLastInput(input) && GetCurrentInput(input);
}

bool Input::IsPrassed(const std::string& input) const
{

	return GetCurrentInput(input);
}

void Input::RewriteInput(const std::string& key, const InputInfo& inputinfo){
	
	auto it = tempTable_.find(key);
	if (it == tempTable_.end())
	{
		assert(0 && "����Ȗ��߂͓o�^����Ă��܂���");
		return;
	}
	for (auto& record : it->second)
	{
		if (inputinfo.type == record.type)
		{
			record.inputID = inputinfo.inputID;
			return;
		}
	}
	//�V�K�o�^
	it->second.push_back(inputinfo);

}

void Input::ComitInputConfig()
{
	inputTable_ = tempTable_;
}

const InputTable_t Input::GetInputTable() const
{
	auto ret = inputTable_;

	for (const auto& ex : excludeOnCongigList_)
	{
		ret.erase(ex);
	}

	return ret;
}

void Input::SaveInputTable()
{
	//FILE* fp=nullptr;
	//fopen_s(&fp, "key.config", "wb");

	//auto size = inputTable_.size();
	//fwrite(&size,sizeof(size),1,fp);

	//for (const auto& record: inputTable_)
	//{
	//	byte strsize = record.first.size();
	//	fwrite(&strsize, sizeof(size), 1, fp);//�R�}���h������
	//	fwrite(record.first.data(), sizeof(char), strsize, fp);//������
	//	//���͂̐�����������
	//	byte inputSize = record.second.size();
	//	fwrite(&inputSize, sizeof(inputSize), 1, fp);//���͐�
	//	for (const auto& inputInfo : record.second)
	//	{
	//		fwrite(&inputInfo, sizeof(inputInfo), 1, fp);
	//	}
	//}
	//fclose(fp);
}

void Input::LoadInputTable()
{

	//auto handle=FileRead_open("key.config");
	//if (handle == 0)
	//{
	//	return;
	//}
	//int size;
	//FileRead_read(&size, sizeof(size),handle);
	//inputTable_.clear();
	//for (int i =0 ; i<size;i++)
	//{
	//	std::string keyname;
	//	byte strsize = 0;
	//	FileRead_read(&strsize, sizeof(strsize), handle);//�R�}���h������
	//	keyname.resize(strsize);
	//	FileRead_read(keyname.data(), strsize, handle);//������
	//	//���͂̐�����������
	//	byte inputSize = 0;
	//	FileRead_read(&inputSize, sizeof(inputSize), handle);//���͐�
	//	for (int i = 0; i < size; i++)
	//	{
	//		InputInfo info;
	//		FileRead_read(&info, sizeof(info), handle);
	//		inputTable_[keyname].push_back(info);
	//	}
	//}
	//FileRead_close(handle);

}

bool Input::CheckExclusiveInput()
{
	char keycode[256];
	GetHitKeyStateAll(keycode);//�L�[�{�[�h����
	int padInfo = GetJoypadInputState(DX_INPUT_PAD1);//�p�b�h�P�ԓ���
	int mouseInfo = GetMouseInput();//�}�E�X����

	for (const auto& exKey: excludeOnCongigList_)
	{
		for (const auto& input : inputTable_[exKey])
		{
			switch (input.type)
			{
			case InputType::keybord:
				if(keycode [input.inputID])
				{
					return true;//�������͂���Ă���
				}
				break;
			case InputType::gamepad:
				if (padInfo& input.inputID)
				{
					return true;//�������͂���Ă���
				}
				break;
			case InputType::mouse:
				if (mouseInfo&input.inputID)
				{
					return true;//�������͂���Ă���
				}
				break;
			default:
				break;
			}
		}
	}

	return false;
}
