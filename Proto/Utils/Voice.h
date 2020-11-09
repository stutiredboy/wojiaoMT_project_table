#ifndef VOICE_H
#define VOICE_H
#include <vector>
#include <string>

/////////////////////////////////////begin/////////////////////////////////////
///////////////////////////////////wav2speex///////////////////////////////////
void voice_encode_init();
int voice_encode(short* in, int size, char* encoded, int max_buffer_size);
std::vector<char> encodeWAV2SPEEX(std::vector<short>& datas);
void voice_encode_release();
///////////////////////////////////speex2wav///////////////////////////////////
void voice_decode_init();
int voice_decode(char* encoded, int size, short* output, int max_buffer_size);
std::vector<short>  decodeSPEEX2WAV(std::string& strData);
void voice_decode_release();

///////////////////////////////////wav2amr///////////////////////////////////
// WAVE��Ƶ����Ƶ����8khz 
// ��Ƶ������Ԫ�� = 8000*0.02 = 160 (�ɲ���Ƶ�ʾ���)
// ������ 1 : 160
//        2 : 160*2 = 320
// bps��������(sample)��С
// bps = 8 --> 8λ unsigned char
//       16 --> 16λ unsigned short
int encodeWAVE2AMR(const char* pchWAVEFilename, const char* pchAMRFileName, int nChannels, int nBitsPerSample);

///////////////////////////////////amr2wav///////////////////////////////////
// ��AMR�ļ������WAVE�ļ�
int decodeAMR2WAV(const char* pchAMRFileName, const char* pchWAVEFilename);

// ���ARM�ļ�����֡��
int getAMRTotalFrames(const char* pchAMRFileName);
/////////////////////////////////////end/////////////////////////////////////

#endif //define VOICE_H
