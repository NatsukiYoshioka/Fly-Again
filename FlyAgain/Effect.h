#pragma once

class Player;

/// <summary>
/// �Q�[���V�[�����̃G�t�F�N�g�𐧌䂷��N���X
/// </summary>
class Effect
{
public:
	/// <summary>
	/// �ϐ��̏������ƃG�t�F�N�g�̃��[�h
	/// </summary>
	Effect();

	/// <summary>
	/// �G�t�F�N�g�n���h���̌㏈��
	/// </summary>
	~Effect();

	/// <summary>
	/// �Đ����Ă���G�t�F�N�g�̈ʒu�X�V
	/// </summary>
	/// <param name="player">�v���C���[����N���X</param>
	void Update(Player* player);

	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �n�ʂɓ����������̃G�t�F�N�g�̍Đ�����
	/// </summary>
	/// <param name="pos">�G�t�F�N�g���Đ�������W</param>
	void UpdateBoundGroundEffect(VECTOR pos);

	/// <summary>
	/// �`�[�Y�ɓ����������̃G�t�F�N�g�̍Đ�����
	/// </summary>
	/// <param name="pos">�G�t�F�N�g���Đ�������W</param>
	void UpdateCheeseEffect(VECTOR pos);

	/// <summary>
	/// �����`����肵���Ƃ��̃G�t�F�N�g�̍Đ�����
	/// </summary>
	/// <param name="pos">�G�t�F�N�g���Đ�������W</param>
	void UpdateWrenchEffect(VECTOR pos);

	/// <summary>
	/// �n�ʂɓ����������̃G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�n�ʂɓ����������̃G�t�F�N�g�̃p�X</returns>
	const char* GetBoundGroundEffectPath();

	/// <summary>
	/// �`�[�Y����肵�����̃G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�`�[�Y����肵�����̃G�t�F�N�g�̃p�X</returns>
	const char* GetCheeseEffectPath();

	/// <summary>
	/// �����`����肵�����̃G�t�F�N�g�̃p�X�擾
	/// </summary>
	/// <returns>�����`����肵�����̃G�t�F�N�g�̃p�X</returns>
	const char* GetWrenchEffectPath();
private:
	int boundGroundEffect;				//�n�ʂɓ����������̃G�t�F�N�g�n���h��
	int boundGroundPlayingEffect;		//�n�ʂɓ����������̍Đ����Ă���G�t�F�N�g�n���h��
	VECTOR boundGroundEffectPos;		//�n�ʂɓ����������̃G�t�F�N�g�̍��W

	int cheeseEffect;					//�`�[�Y����肵�����̃G�t�F�N�g�n���h��
	int cheesePlayingEffect;			//�`�[�Y����肵�����̍Đ����Ă���G�t�F�N�g�n���h��
	VECTOR cheeseEffectPos;				//�`�[�Y����肵�����̃G�t�F�N�g�̍��W

	int wrenchEffect;					//�����`����肵�����̃G�t�F�N�g�n���h��
	int wrenchPlayingEffect;			//�����`����肵�����̍Đ����Ă���G�t�F�N�g�n���h��
	VECTOR wrenchEffectPos;				//�����`����肵�����̃G�t�F�N�g�̍��W

	static constexpr int initialBoundGroundPlayingEffect = 0;		//�n�ʂɓ����������̍Đ����Ă���G�t�F�N�g�n���h���̏������p�萔
	static constexpr int initialCheesePlayingEffect = 0;			//�`�[�Y����肵�����̍Đ����Ă���G�t�F�N�g�n���h���̏������p�萔
	static constexpr int initialWrenchPlayingEffect = 0;			//�����`����肵�����̍Đ����Ă���G�t�F�N�g�n���h���̏������p�萔
	static constexpr float effectScale = 15.0f;						//�G�t�F�N�g�̃X�P�[��
	static const VECTOR initialBoundGroundEffectPos;				//�n�ʂɓ����������̃G�t�F�N�g�̍��W�̏������p�萔
	static const VECTOR initialCheeseEffectPos;						//�`�[�Y����肵�����̃G�t�F�N�g�̍��W�̏������p�萔
	static const VECTOR initialWrenchEffectPos;						//�����`����肵�����̃G�t�F�N�g�̍��W�̏������p�萔
	static constexpr const char* boundGroundEffectPath = "data/effect/boundground.efk";		//�n�ʂɓ����������̃G�t�F�N�g�̃p�X
	static constexpr const char* cheeseEffectPath = "data/effect/getcheese.efk";			//�`�[�Y����肵�����̃G�t�F�N�g�̃p�X
	static constexpr const char* wrenchEffectPath = "data/effect/bounditem.efk";			//�����`����肵�����̃G�t�F�N�g�̃p�X
};

