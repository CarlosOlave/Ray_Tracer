#include "parse.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void Parser::SetTriangle(std::vector<float3> &collection, 
						 std::vector<float3> &normalCollection) {

	if (collection.size() != 3) return;
	if (normalCollection.size() != 3) return;
	
	float3 v0 = collection[0];
	float3 v1 = collection[1];
	float3 v2 = collection[2];
	
	float3 vn0 = normalCollection[0];
	float3 vn1 = normalCollection[1];
	float3 vn2 = normalCollection[2];
	
	triangle(v0, v1, v2,
			 vn0, vn1, vn2);
}

void Parser::ReadObj(char *_name) {
	Mesh object;
	int normal_flag = object.loadFile(_name, 0);
	
	if (!normal_flag)
		object.setNormal();
	
	std::vector<float3> float3Collection;
	std::vector<float3> float3NormalCollection;
	
	int n_Group = object.m_nGroup;
	int t_index;
	int eid;
	int start_eid;
	int vid;
	int nid;
	int n_count;
	float3 point;
	float3 point_normal;
	
	for (int i = 0; i < n_Group; i++) {
		int t_size = object.groups[i].tids.size();
		for (int k = 0 ; k < t_size; k++) {
			t_index = object.groups[i].tids[k];
			
			eid = object.triangles[t_index].edge_id;
			start_eid = eid;
			n_count = 0;
			do {
				vid = object.edges[eid].vertex_id;
				nid = object.triangles[t_index].normal_id[n_count];
				
				if (nid == -1) {
					point_normal.x = object.vertex[vid].normal.x;
					point_normal.y = object.vertex[vid].normal.y;
					point_normal.z = object.vertex[vid].normal.z;
				}else {
					point_normal.x = object.normals[nid].normal.x;
					point_normal.y = object.normals[nid].normal.y;
					point_normal.z = object.normals[nid].normal.z;
				}

				
				point.x = object.vertex[vid].position.x;
				point.y = object.vertex[vid].position.y;
				point.z = object.vertex[vid].position.z;
				float3Collection.push_back(point);
				float3NormalCollection.push_back(point_normal);
				
				n_count++;
				eid = object.edges[eid].next_id;
				
			} while (eid != start_eid);
			
			SetTriangle(float3Collection, float3NormalCollection);
			float3Collection.clear();
			float3NormalCollection.clear();
		}
	}	
}

void Parser::parse(const char *file) {
  ifstream in(file);
  char buffer[1025];
  string cmd;

  for (int line=1; in.good(); line++) {
    in.getline(buffer,1024);
    buffer[in.gcount()]=0;

    cmd="";

    istringstream iss(buffer);

    iss >> cmd;
    if (cmd[0]=='/' || cmd.empty()) {
      continue;
	} else if (cmd=="obj") {
	  char _name[] = "";
	  iss >> _name;
	  ReadObj(_name);
    } else if (cmd=="s") {
      float3 pos; float r;
      iss >> pos >> r;
      sphere(pos,r);
    } else if (cmd=="t") {
      float3 a,b,c;
      iss >> a >> b >> c;
      triangle(a,b,c);
    } else if (cmd=="p") {
      float3 n; float d;
      iss >> n >> d;
      plane(n,d);
    } else if (cmd=="c") {
      float3 pos,dir; float d,iw,ih; int pw,ph;
      iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
      camera(pos,dir,d,iw,ih,pw,ph);
    } else if (cmd=="l") {
      iss >> cmd;
      if (cmd=="p") {
	float3 pos,rgb;
	iss >> pos >> rgb;
	pointLight(pos,rgb);
      } else if (cmd=="d") {
	float3 dir,rgb;
	iss >> dir >> rgb;
	directionalLight(dir,rgb);
      } else if (cmd=="a") {
	float3 rgb;
	iss >> rgb;
	ambientLight(rgb);
      } else {
	cout << "Parser error: invalid light at line " << line << endl;
      }
    } else if (cmd=="m") {
      float3 diff,spec,refl; float r;
      iss >> diff >> spec >> r >> refl;
      material(diff,spec,r,refl);
    } else {
      cout << "Parser error: invalid command at line " << line << endl;
    }
  }
  
  in.close();
}
