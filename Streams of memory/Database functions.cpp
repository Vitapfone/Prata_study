#include "pch.h"
#include "Image.h"
#include "Link.h"

//���������� ���������� ����������� ���� ������ �� ������.
void database_initialization(const string & images_file, const string & links_file, const string & strings_file, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings)
{
	//��������������� ������� �� ������.

	ifstream ifs_Images(images_file, ifstream::binary);
	Image temp1;//��������� ������ ������.

	while (temp1.bin_read(ifs_Images))//������ �� ����� �� ��������� ������.
	{
		images[temp1.get_id()] = temp1;
	}

	//������ ������ �� �����.

	ifstream ifs_links(links_file, ifstream::binary);
	Link temp2;

	while (temp2.bin_read(ifs_links))
	{
		links[temp2.get_id()] = temp2;
	}

	//������ ����� �� �����.

	ifstream ifs_str(strings_file, ifstream::binary);
	Id_string temp3;//��������� ������ ������.

	while (temp3.bin_read(ifs_str))//���� �� ��������� ����� �����.
	{
		//��������� ����������� � �����.
		strings[temp3.get_id()] = temp3;
	}


	//������� ��� ������� ����-�-������.

	//������ �������� �����.
	for (auto & e : images)
	{
		auto & curr_image = e.second;
		auto & link = links[curr_image.get_is_link().id_];
		curr_image.set_is_link(&link);
	}

	//����� �������� ���� ��������� �� ������ � ������.
	for (auto & e : links)
	{
		Link & curr_link = e.second;
		Image & image = images[curr_link.get_left_id()];
		curr_link.set_left_ptr(&image);
		Id_string & string = strings[curr_link.get_right_id()];
		curr_link.set_right_ptr(&string);
	}
	
	//������ �������� �����.
	for (auto & e : strings)
	{
		Id_string & curr_string = e.second;
		Link & link = links[curr_string.get_link_id()];
		curr_string.set_is_link(&link);	
	}
}

//������ ����������� ����������� � �����.
void database_recording(const string & images_file, const string & links_file, const string & strings_file, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings)
{
	ofstream ofsImages(images_file, ofstream::binary);//������� ���� ��� ������ �������. ����� ������ ���� ������� �������.
	//����������� ��� ������.
	for (const auto & e : images)
	{
		e.second.bin_write(ofsImages);
	}

	ofstream ofs_links(links_file, ofstream::binary);
	//���������� ��� �����.
	for (const auto & e : links)
	{
		e.second.bin_write(ofs_links);
	}

	ofstream ofstrings(strings_file, ofstream::binary);//������� ���� ��� ������ ��������� � �������� �����.
	//���������� ��� ������ �� �����.
	for (const auto &e : strings)
	{
		e.second.bin_write(ofstrings);
	}
}
