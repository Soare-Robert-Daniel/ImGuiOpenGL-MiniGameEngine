//
// Created by Robert on 10.11.2022.
//

#include "Model.h"

void Model::LoadFromFile(const std::string &filename) {
  std::cout << "> Loading 3D model from: " << filename << std::endl;
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(filename,
										   aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
											   | aiProcess_CalcTangentSpace);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
  {
	std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
	return;
  }

  NodeImporterHandler(scene->mRootNode, scene);
}

void Model::NodeImporterHandler(aiNode *node, const aiScene *scene) {
  std::cout << "  | Reading " << node->mNumMeshes << " meshes." << std::endl;

  for (auto meshIdx = 0; meshIdx < node->mNumMeshes; meshIdx++) {
	auto mesh = scene->mMeshes[node->mMeshes[meshIdx]];
	meshes.push_back(CreateMeshFromNode(mesh));
  }

  std::cout << "  | Loaded " << meshes.size() << " meshes." << std::endl;

  for (auto nodeIdx = 0; nodeIdx < node->mNumChildren; nodeIdx++) {
	std::cout << "| Going to the next node: " << nodeIdx << std::endl;
	NodeImporterHandler(node->mChildren[nodeIdx], scene);
  }
}

std::shared_ptr<Mesh> Model::CreateMeshFromNode(aiMesh *mesh) {
  std::vector<CGE::Vertex> vertices;
  std::vector<unsigned int> indices;


  for (auto vertIdx = 0; vertIdx < mesh->mNumVertices; vertIdx++) {
	CGE::Vertex vertex{.color = glm::vec4(0.0f)};

	// POSITION
	vertex.position = glm::vec3(
		mesh->mVertices[vertIdx].x,
		mesh->mVertices[vertIdx].y,
		mesh->mVertices[vertIdx].z
	);

	// NORMALS
	if (mesh->HasNormals()) {
	  vertex.normal = glm::vec3(
		  mesh->mNormals[vertIdx].x,
		  mesh->mNormals[vertIdx].y,
		  mesh->mNormals[vertIdx].z
	  );
	}

	// TEXTURE COORDINATES
	if (mesh->mTextureCoords[0]) {
	  vertex.textCoords = glm::vec2(
		  mesh->mTextureCoords[0][vertIdx].x,
		  mesh->mTextureCoords[0][vertIdx].y
	  );
	} else {
	  vertex.textCoords = glm::vec2(0.0f, 0.0f);
	}

	vertices.push_back(vertex);
  }

  for (auto faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
	aiFace face = mesh->mFaces[faceIdx];
	// retrieve all indices of the face and store them in the indices vector
	for (auto indIdx = 0; indIdx < face.mNumIndices; indIdx++)
	  indices.push_back(face.mIndices[indIdx]);
  }

  std::shared_ptr<Mesh> new_mesh(new Mesh("model"));
  new_mesh->AddVertices(vertices);
  new_mesh->AddIndices(indices);
  new_mesh->LoadToGPU();

  return new_mesh;
}

void Model::RenderMeshes() {
  for (auto &mesh : meshes) {
	mesh->Render();
  }
}
