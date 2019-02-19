#include "pch.h"
#include "Image.h"
#include "Link.h"

//���������� ���������� ����������� ���� ������ �� ������.
void database_initialization(const string & file1, const string & file2, const string & file3, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings)
{
	//��������������� ������� �� ������.

	ifstream ifs_Images(file1, ifstream::binary);
	Image temp1;//��������� ������ ������.

	while (temp1.bin_read(ifs_Images))//������ �� ����� �� ��������� ������.
	{
		images[temp1.get_id()] = temp1;
	}

	//������ ������ �� �����.

	ifstream ifs_links(file2, ifstream::binary);
	Link temp2;

	while (Links::bin_read(ifs_links, temp2))
	{
		cout << "link inserting\n";
		links[temp2.get_id()] = temp2;
	}

	//������ ����� �� �����.

	ifstream ifs_str(file3, ifstream::binary);
	Id_string temp3;//��������� ������ ������.

	while (temp3.bin_read(ifs_str))//���� �� ��������� ����� �����.
	{
		strings[temp3.get_id()] = temp3;//��������� ����������� � �����.
	}


	//������� ��� ������� ����-�-������.

	for (auto & e : images)
	{
		auto & curr_image = e.second;
		auto & link = links[curr_image.get_is_link().id];
		curr_image.set_is_link(&link);
		cout << "curr_image.get_is_link = " << curr_image.get_is_link().id << endl;
	}

	for (auto & e : links)
	{
		cout << "for : links\n";
		Link & curr_link = e.second;
		Image & image = images[curr_link.get_left_id()];
		curr_link.set_left_ptr(&image);
		Id_string & string = strings[curr_link.get_right_id()];
		curr_link.set_right_ptr(&string);
	}
	cout << links.size() << endl;
	for (auto & e : strings)
	{
		Id_string & curr_string = e.second;
		Link & link = links[curr_string.get_link_id()];
		curr_string.set_is_link(&link);
		cout << "curr_string.get_link_id() = " << curr_string.get_link_id() << endl;
	}
	cout << links.size() << endl;
}

//������ ����������� ����������� � �����.
void database_recording(const string & file1, const string & file2, const string & file3, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings)
{
	ofstream ofsImages(file1, ofstream::binary);//������� ���� ��� ������ �������.
	for (const auto & e : images)
	{
		e.second.bin_write(ofsImages);
	}

	ofstream ofs_links(file2, ofstream::binary);
	for (const auto & e : links)
	{
		Links::bin_write(ofs_links, e.second);
	}

	ofstream ofstrings(file3, ofstream::binary);//������� ���� ��� ������ ��������� � �������� �����. ����� ������ ���� ������� �������.
	for (const auto &e : strings)//���������� ��� ������ �� �����.
	{
		e.second.bin_write(ofstrings);
	}
	
}
