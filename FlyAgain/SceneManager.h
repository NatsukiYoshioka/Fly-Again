#pragma once

class BaseScene;

/// <summary>
/// �V�[���S�̂��Ǘ��A���䂷��N���X
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// �V�[���̏�Ԃ��Ǘ�
	/// </summary>
	enum class SCENE
	{
		TITLE,								//�^�C�g�����
		GAME,								//�Q�[�����
		RESULT								//���U���g���
	};

	/// <summary>
	/// �Q�[���I���������̏��
	/// </summary>
	enum class FINISH_CONDITION
	{
		INGAME,								//�Q�[����
		PERFECT,							//�p�[�t�F�N�g�N���A
		CLEAR,								//�ʏ�N���A
		GAMEOVER							//�Q�[���I�[�o�[
	};

	/// <summary>
	/// �V�[���̏�����
	/// </summary>
	SceneManager();

	/// <summary>
	/// �N���X�̌㏈��
	/// </summary>
	~SceneManager() {}

	/// <summary>
	/// �V�[���������ɂ���ĕς���֐�
	/// </summary>
	/// <param name="scene">�ύX����V�[��</param>
	static void ChangeScene(SCENE scene);

	/// <summary>
	/// �Q�[���I�����̏�Ԃ�ύX����֐�
	/// </summary>
	/// <param name="condition">�Q�[���I�����̏��</param>
	static void ChangeCondition(FINISH_CONDITION condition);

	/// <summary>
	/// ���݂̃V�[���̍X�V
	/// </summary>
	static void Update();

	/// <summary>
	/// ���݂̃V�[���̕`��
	/// </summary>
	static void Draw();

	/// <summary>
	/// �Q�[���I�����̏�Ԃ��擾
	/// </summary>
	/// <returns>�Q�[���I�����̏��</returns>
	static FINISH_CONDITION GetCondition() { return _condition; }
private:
	static BaseScene* nowScene;					//���݂̃V�[��
	static FINISH_CONDITION _condition;			//�Q�[���I�����̏��
};