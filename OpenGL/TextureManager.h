//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#ifndef TextureManager_H
#define TextureManager_H

#include <windows.h>
#include <gl/gl.h>
#include <FreeImage.h>
#include <map>

#define TEXTUREMANAGER TextureManager::Inst()

class TextureManager
{
public:
	//ͼƬ������ĵ�����������
	static TextureManager* Inst();
	virtual ~TextureManager();//����

	//load a texture and make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	bool LoadTexture(
		const char* filename,				//Ҫ���ص��ļ���
		const unsigned int texID,			//�Զ����ͼƬID����OpenGL�����ģ�
											//���������ֵ�Եļ�ֵ
											//��Ϊ����ʹ�õ���map���洢��
											//����������
		GLenum image_format = GL_RGB,		//�����ͼƬ��ɫ��ʽ
		GLint internal_format = GL_RGB,		//ͼƬ�洢��ʽ
		GLint level = 0,					//�༶ͼƬ�ȼ�
		GLint border = 0);					//ͼƬ�߽�ߴ�

	//�����Զ���ͼƬIDж������
	//free the memory for a texture
	bool UnloadTexture(const unsigned int texID);

	//�Զ����ͼƬID������
	//set the current texture
	bool BindTexture(const unsigned int texID);//�Զ����ͼƬID������

	//һ����ȫ��ж�����е�����
	//free all texture memory
	void UnloadAllTextures();

protected:
	TextureManager();//����
	TextureManager(const TextureManager& tm);//��������
	TextureManager& operator=(const TextureManager& tm);//�ȺŸ�ֵ

	static TextureManager* m_inst;//��������ָ��
	std::map<unsigned int, GLuint> m_texID;//�洢ͼ��ID��map��
};

#endif