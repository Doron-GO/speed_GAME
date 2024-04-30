#pragma once
#include<DxLib.h>
class PostEfffect
{
public:

	// �s�N�Z���V�F�[�_�p�I���W�i���萔�o�b�t�@�̎g�p�J�n�X���b�g
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 4;

	// ���_��
	static constexpr int NUM_VERTEX = 4;

	// ���_�C���f�b�N�X��
	static constexpr int NUM_VERTEX_IDX = 6;

	// �|���S����
	static constexpr int NUM_POLYGON = 2;


	PostEfffect(int &screenID);
	~PostEfffect();

	void Update();
	void Draw();

	VERTEX2DSHADER vertexs_[NUM_VERTEX];
	// ���_�C���f�b�N�X
	WORD indexes_[NUM_VERTEX_IDX];

private:

	void MakeSquereVertex(void);
	int& mainScreen_;
	int screen_;
	int ShaderHandle_;
	int constBuf_;

};

