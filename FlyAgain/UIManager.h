#pragma once

/// <summary>
/// UI�摜�Ǘ��N���X
/// </summary>
class UIManager
{
public:
	/// <summary>
	/// UI�摜�̃��[�h
	/// </summary>
	UIManager();

	/// <summary>
	/// UI�摜�̌㏈��
	/// </summary>
	~UIManager();

	/// <summary>
	/// �n�[�g�摜�n���h���擾
	/// </summary>
	/// <returns>�n�[�g�摜�n���h��</returns>
	static int GetHeartImgHandle() { return heartImgHandle; }

	/// <summary>
	/// ����n�[�g�摜�n���h���擾
	/// </summary>
	/// <returns>����n�[�g�摜�n���h��</returns>
	static int GetBrokenHeartImgHandle() { return brokenHeartImgHandle; }

	/// <summary>
	/// �����`�摜�n���h���擾
	/// </summary>
	/// <returns>�����`�摜�n���h��</returns>
	static int GetWrenchImgHandle() { return wrenchImgHandle; }

	/// <summary>
	/// ���w�i�摜�n���h���擾
	/// </summary>
	/// <returns>���w�i�摜�n���h��</returns>
	static int GetBlackBackGroundHandle() { return blackBackGroundHandle; }

	/// <summary>
	/// �~�摜�n���h���擾
	/// </summary>
	/// <returns>�~�摜�n���h��</returns>
	static int GetCircleImgHandle() { return circleImgHandle; }

	/// <summary>
	/// �~�`�[�Y�摜�n���h���擾
	/// </summary>
	/// <returns>�~�`�[�Y�摜�n���h��</returns>
	static int GetCircleCheeseImgHandle() { return circleCheeseImgHandle; }

	/// <summary>
	/// �����摜�n���h���擾
	/// </summary>
	/// <returns>�����摜�n���h��</returns>
	static int GetHoleImgHandle() { return holeImgHandle; }

	/// <summary>
	/// A�{�^���摜�n���h���擾
	/// </summary>
	/// <returns>A�{�^���摜�n���h��</returns>
	static int GetButtonAImgHandle() { return buttonAImgHandle; }

	/// <summary>
	/// �I��p�`�[�Y�}�[�J�[�摜�n���h���擾
	/// </summary>
	/// <returns>�I��p�`�[�Y�}�[�J�[�摜�n���h��</returns>
	static int GetCheeseMarkerImgHandle() { return cheeseMarkerImgHandle; }

	const char* GetHeartTexturePath();				//�n�[�g�摜�̃p�X�擾
	const char* GetBrokenHeartTexturePath();		//����n�[�g�摜�̃p�X�擾
	const char* GetWrenchTexturePath();				//�����`�摜�̃p�X�擾
	const char* GetBlackBackGroundPath();			//���w�i�摜�̃p�X�擾
	const char* GetCircleTexturePath();				//�~�Q�[�W�摜�p�X�擾
	const char* GetCircleCheeseTexturePath();		//�`�[�Y�~�Q�[�W�p�摜�̃p�X�擾
	const char* GetHoleTexturePath();				//�����摜�̃p�X�擾
	const char* GetButtonATexturePath();			//A�{�^���摜�̃p�X�擾
	const char* GetCheeseMarkerTexturePath();		//�I��p�`�[�Y�}�[�J�[�摜�̃p�X�擾
private:
	static int heartImgHandle;							//�n�[�g�摜�n���h��
	static int brokenHeartImgHandle;					//����n�[�g�摜�n���h��
	static int wrenchImgHandle;							//�����`�摜�n���h��
	static int blackBackGroundHandle;					//���w�i�n���h��
	static int circleImgHandle;							//�~�Q�[�W�n���h��
	static int circleCheeseImgHandle;					//�`�[�Y�~�Q�[�W�p�摜�n���h��
	static int holeImgHandle;							//�����摜�n���h��
	static int buttonAImgHandle;						//A�{�^���摜�n���h��
	static int cheeseMarkerImgHandle;					//�I��p�`�[�Y�}�[�J�[�摜�n���h��
};

