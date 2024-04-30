#pragma once
#include<DxLib.h>

#include<string>
#include<unordered_map>
#include<vector>

//���͎��
enum class InputType {
	keybord,//�L�[�{�[�h
	gamepad,//�Q�[���p�b�h
	mouse	//�}�E�X
};

//���͏��(�������)
struct InputInfo {
	InputType type;//���͎��
	//���ۂɒ��ׂ�l(PAD��}�E�X�Ȃ�r�b�g��\���L�[�{�[�h�Ȃ�L�[�R�[�h��)
	//�\��
	int inputID;
};

//���͂̏�Ԃ�ێ����邽�߂̍\����
//struct InputState 
//{
//	std::string key;//�Ώۂ̓��͂�����킷����
//	bool isPressed=false;//���̑Ώۂ�������Ă��邩�ǂ���
//
//};

//�Q�[�����̈Ӗ��Ɠ��͂��ꂽ���ǂ������y�A�ɂ�������
//�Ƃɂ����Ώۂ́u�Ӗ��v�������ꂽ�炠���n��true�ɂȂ�^
using InputState_t = std::unordered_map<std::string, bool>;

//�Q�[������"�Ӗ�"�Ǝ��ۂ̃L�[�R�[�h�̃y�A
//�L�[(first)�͖��߂̈Ӗ��A
//�Q�[�����̈Ӗ��Ǝ��ۂ̈Ӗ��̓���(�n�[�h����)�̑Ή��\��\���u�^�v
using InputTable_t =
std::unordered_map<std::string, std::vector<InputInfo>>;

class KeyConfigScene;

class Input
{
	friend KeyConfigScene;
private:
	
	std::vector<std::string>excludeOnCongigList_;//�L�[�R���t�B�O���O���X�g

	//�Ӗ��ƃn�[�h���͂̑Ή��\
	InputTable_t  inputTable_;
	InputTable_t  tempTable_;

	//�������L�^
	InputState_t lastState_={};//������
	InputState_t currentState_={};//��


	//�l�̑���ƃR�s�[�̋֎~
	Input(const Input&) = delete;
	void operator = (const Input&) = delete;

	//���݂��̃L�[��������Ă��邩
	bool GetCurrentInput(const std::string& input)const;
	//���O�ɂ��̃L�[��������Ă��邩
	bool GetLastInput(const std::string& input)const;


public:
	Input();
	/// <summary>
	/// �L�[���͏����X�V����(���t���[��)
	/// </summary>
	void Update(int padNum);
	/// <summary>
	/// ���������u�Ԃ��ǂ�����Ԃ�(�������ςȂ���false)
	/// </summary>
	/// <param name="input">���͎���(next��pause)</param>
	/// <returns></returns>
	bool IsTriggerd(const std::string& input)const;
	/// <summary>
	/// �����������ǂ�����Ԃ�
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	bool IsPrassed(const std::string& input)const;

	/// <summary>
	/// ���̓e�[�u���̏�������
	/// </summary>
	/// <param name="key">���ߕ�����</param>
	/// <param name="inputinfo">�@�킩��̓��͏��(�n�[�h)</param>
	void RewriteInput(const std::string& key,const InputInfo& inputinfo);

	void ComitInputConfig();

	//���̓e�[�u�����̂�\������
	const InputTable_t GetInputTable()const;

	void SaveInputTable();
	void LoadInputTable();

	/// <summary>
	/// ���݂̓��͂����O���͂ɓ�����̂��ǂ������`�F�b�N����
	/// </summary>
	/// <returns>true:���O���͂ɓ�����,false:������Ȃ�</returns>
	bool CheckExclusiveInput();

	DINPUT_JOYSTATE joyDInState_;

};

