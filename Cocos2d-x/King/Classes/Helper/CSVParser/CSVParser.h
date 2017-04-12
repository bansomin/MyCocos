/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	: CSV�ļ�����
VERSION	:
HISTORY	:
***************************END****************************************************/

//��1�������ռ�	��CSVParser
//��2��Row��		��һ�е����ݼ�¼��������[] �����������ͨ������ֵ�ԡ���ʽ��ȡ����ֵ��
//��3��Csv��		������csv�ļ���������[] �����������������һ����ȡ����ֵ��

#ifndef _CSVParser_H_
#define _CSVParser_H_

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
#include <string>
using namespace  std;


namespace CSVParser
{

	// ÿһ�еļ�¼
	class Row {
		public:
		Row() {}
		~Row() {}

		void push_back(const string& value) { m_values.push_back(value); }
		void setHeader(const vector<string>* header) { m_header = header; }

		public:

		// ÿ�������ж����ֶ�
		int size() const { return m_values.size(); }

		// ����� [] ����
		string& operator[](int key) {
			if(key < size()) return m_values[key];
			throw "can't return this value (doesn't exist)";
		}

		// ����� [] ����
		string& operator[](const string& key) {
			vector<string>::const_iterator it;
			int pos = 0;
			for(it = (*m_header).begin(); it!=(*m_header).end(); it++) {
				if(key==*it) return m_values[pos];
				pos++;
			}
			throw "can't return this value (doesn't exist)";
		}

		private:
		const vector<string>* m_header;
		vector<string> m_values;
	};


	class Csv {
		public:
		Csv(const string& filename);
		~Csv();

		// ����csv�ļ�
		void Parse(const string& filename);

		// ������Ϣ
		const string& getErrorInfo() const { return m_strErrorInfo; }

		// ��ȡ��ͷ�ֶ�
		vector<string> getHeader() const { return m_header; }
		// ��ȡ������
		int getRowCount() const { return m_content.size(); }
		// ��ȡ������
		int getColumnCount() const { return m_header.size(); }
		// ����� [] ����
		Row& operator[](int key);

		private:
		// ��ȡ�����ļ�������
		void Load(const string& filename, string& Data);
		void setHeader();

		private:
		// ԭʼ�������
		vector<Row> m_content;   // �����е����ݣ�������ͷ��
		vector<string> m_header; // ��ͷ�ֶ�
								 // ������Ϣ
		string m_strErrorInfo;
	};
}


#endif  // _CSVParser_H_




