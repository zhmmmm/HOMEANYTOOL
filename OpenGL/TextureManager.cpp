//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************
#include "TextureManager.h"
//ʹ�������ķ�ʽ����Ҫ���ӵľ�̬��
#pragma comment(lib,"FreeImage.lib")

TextureManager* TextureManager::m_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!m_inst)
		m_inst = new TextureManager();

	return m_inst;
}

TextureManager::TextureManager()
{
	//����ǰ��վ�̬��ķ�ʽʹ��FreeImage����ô��Ҫ��ʼ��
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}
	
TextureManager::~TextureManager()
{
	//����ǰ��վ�̬��ķ�ʽʹ��FreeImage����ô��Ҫ����
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	UnloadAllTextures();
	if (m_inst)
	{
		delete m_inst;
	}
	m_inst = 0;
}

bool TextureManager::LoadTexture(
								 const char* filename,
								 const unsigned int texID,
								 GLenum image_format, 
								 GLint internal_format, 
								 GLint level, 
								 GLint border)
{
	//ͼƬ��ʽ
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	//ָ��ͼƬ�������˵���ָ�룬ֻ����һ�Σ�FreeImage����ͼƬ��Ҫ�����ָ��
	//�е����ƴ��ļ����ص�һ���ļ�ָ�룬ͨ�����ָ����Բ����ļ�
	//pointer to the image, once loaded
	FIBITMAP *dib(0);//FIBITMAP *dib=NULL;


	//ָ���ͼƬ����ɫ����
	//pointer to the image data
	BYTE* bits(0);

	//ͼƬ�Ŀ�͸�
	//image width and height
	unsigned int width(0), height(0);


	//Ҫ�ŵ�map�е�OpenGL ��ͼƬID
	//OpenGL's image ID to map to
	GLuint gl_texID;
	
	//�����ļ�ǩ��(�ļ�ͷ)�ƶ��ļ�����
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//�����Ȼ�������ʽ�����Դ��ļ���չ���²��ļ���ʽ
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);

	//�����Ȼ�������ʽ�����ؼ�
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;


	//�����ʽ����ͼƬ���FreeImage��ͼƬָ��
	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	
	//����ļ�����ʧ�ܣ����ؼ�
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//����ͼƬ����ɫ����
	//retrieve the image data
	bits = FreeImage_GetBits(dib);

	//��ȡͼƬ�Ŀ��
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	//����ͼƬ�����Ƿ�Ϻ��߼�
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		return false;
	

	//���������Զ���ID�Ѿ���ʹ�ã�ж�ص�ǰ�Զ���ID������OpenGLͼƬ����
	//if this texture ID is in use, unload the current texture
	if(m_texID.find(texID) != m_texID.end())
		glDeleteTextures(1, &(m_texID[texID]));


	//���´���OpenGLͼƬ����
	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//store the texture ID mapping
	m_texID[texID] = gl_texID;
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexParameterf(
		GL_TEXTURE_2D,//��ά�����������
		GL_TEXTURE_MIN_FILTER,//��С����
		GL_LINEAR);//������ʽ
	glTexParameterf(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,//�Ŵ����
		GL_LINEAR);
	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	//��������ͼƬ������ж��ͼƬ
	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);
	glBindTexture(GL_TEXTURE_2D,0);
	//return success
	return true;
}

bool TextureManager::UnloadTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if(m_texID.find(texID) != m_texID.end())
	{
		glDeleteTextures(1, &(m_texID[texID]));
		m_texID.erase(texID);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(m_texID.find(texID) != m_texID.end())
		glBindTexture(GL_TEXTURE_2D, m_texID[texID]);
	//otherwise, binding failed
	else
		result = false;

	return result;
}

void TextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<unsigned int, GLuint>::iterator i = m_texID.begin();

	//Unload the textures untill the end of the texture map is found
	while(i != m_texID.end())
		UnloadTexture(i->first);

	//clear the texture map
	m_texID.clear();
}