#include "InterfaceCreation.h"

// Getters from user
std::string getStringFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    char userText[MAX_LENGTH_STRING_FROM_USER];
    while (true) {
        if (question != "")
            std::cout << question << std::endl;
        std::cout << prompt;
        std::cin.getline(userText, MAX_LENGTH_STRING_FROM_USER);
        if (std::cin.fail()) {
            std::cout << "This string is too long." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return userText;
    }
}

char getLowerCaseCharFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    return std::tolower((getStringFromUser(question, prompt))[0]);
}

int getIntFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    while (true) {
        std::string userText = getStringFromUser(question, prompt);

        try {
            return std::stoi(userText);
        }
        catch (const std::invalid_argument& exception) {
            std::cout << "This is not a number!";
        }
        catch (const std::out_of_range& exception) {
            std::cout << "This number is too big! (What were you expecting?)";
        }

        std::cout << std::endl << std::endl;
    }
}

unsigned int getUnsignedIntFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    while (true) {
        int value = getIntFromUser(question, prompt);
        if (value >= 0)
            return value;
        std::cout << "This is not a positive number!" << std::endl << std::endl;
    }
}

double getDoubleFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    while (true) {
        std::string userText = getStringFromUser(question, prompt);

        try {
            return std::stod(userText);
        }
        catch (const std::invalid_argument& exception) {
            std::cout << "This is not a number!";
        }
        catch (const std::out_of_range& exception) {
            std::cout << "This number is either too big or with too many decimals.";
        }

        std::cout << std::endl << std::endl;
    }
}

double getPositiveDoubleFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    while (true) {
        double value = getDoubleFromUser(question, prompt);
        if (value >= 0)
            return value;
        std::cout << "This is not a positive number!" << std::endl << std::endl;
    }
}

bool getBoolFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    while (true) {
        char userText = getLowerCaseCharFromUser(question, prompt);

        if (userText == 't')
            return true;
        else if (userText == 'f')
            return false;
        else
            std::cout << "This is not a boolean!" << std::endl << std::endl;

    }
}

DoubleVec3D getXYZDoubleVec3DFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    // Use array?
    double x = getDoubleFromUser(question, "x " + prompt);
    double y = getDoubleFromUser("", "y " + prompt);
    double z = getDoubleFromUser("", "z " + prompt);

    return DoubleVec3D(x, y, z);
}

DoubleVec3D getRGBDoubleVec3DFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
    // Use array?
    double x = getPositiveDoubleFromUser(question, "r " + prompt);
    double y = getPositiveDoubleFromUser("", "g " + prompt);
    double z = getPositiveDoubleFromUser("", "b " + prompt);

    return DoubleVec3D(x, y, z);
}


// Material creation
Material* createDiffuseMaterial(const DoubleVec3D& emittance) {
    DoubleVec3D albedo = getRGBDoubleVec3DFromUser("What is the albedo of this diffuse material? (each component should be between 0 and 1)");
    std::cout << std::endl;
    return new DiffuseMaterial(albedo, emittance);
}

Material* createRefractiveMaterial(const DoubleVec3D& emittance) {
    double refractiveIndex = getPositiveDoubleFromUser("What is the refractive index of this material? (1 = no refraction / 1.5 = glass)");
    std::cout << std::endl;
    return new RefractiveMaterial(refractiveIndex, emittance);
}

Material* createSpecularMaterial(const DoubleVec3D& emittance) {
    return new SpecularMaterial(emittance);
}

Material* createMaterial() {
    while (true) {
        char command = getLowerCaseCharFromUser("Do you want a (d)iffuse material, a (r)efractive material or a (s)pecular material?");
        if (command == 'd' || command == 'r' || command == 's') {
            std::cout << std::endl;
            DoubleVec3D emittance = getRGBDoubleVec3DFromUser("What is the emittance of this material? ((0, 0, 0) if not a lamp)");
            std::cout << std::endl;

            switch (command) {
            case 'd': return createDiffuseMaterial(emittance);
            case 'r': return createRefractiveMaterial(emittance);
            case 's': return createSpecularMaterial(emittance);
            }
        }
        else
            std::cout << INVALID_COMMAND << std::endl << std::endl;
    }
}


// Object creation
Object3D* createSphere(Material* material) {
    DoubleVec3D center = getXYZDoubleVec3DFromUser("What is the center of the sphere?");
    std::cout << std::endl;
    double radius = getPositiveDoubleFromUser("What is the radius of the sphere?");
    std::cout << std::endl;

    return new Sphere(center, radius, material);
}

Object3D* createTriangle(Material* material) {
    DoubleVec3D vertex0 = getXYZDoubleVec3DFromUser("What is the first vertex of the triangle? (Order is important for the normal, give them counterclockwise from where they are visible.)");
    std::cout << std::endl;
    DoubleVec3D vertex1 = getXYZDoubleVec3DFromUser("What is the second vertex of the triangle?");
    std::cout << std::endl;
    DoubleVec3D vertex2 = getXYZDoubleVec3DFromUser("What is the third vertex of the triangle?");
    std::cout << std::endl;

    return new Triangle(vertex0, vertex1, vertex2, material);
}

Object3D* createObject3D() {
    while (true) {
        char command = getLowerCaseCharFromUser("Do you want a (s)phere or a (t)riangle?");
        if (command == 's' || command == 't') {
            std::cout << std::endl;
            Material* material = createMaterial();

            switch (command) {
            case 's': return createSphere(material);
            case 't': return createTriangle(material);
            }
        }
        else
            std::cout << INVALID_COMMAND << std::endl << std::endl;
    }
}


// From/to json
void to_json(json& j, const Material& mat) {
    j = json{ {"MaterialType", mat.getType()},  {"Emittance", mat.getEmittance()}, {"SpecificParameters", mat.getSpecificParametersJson()} };
}

Material* importMaterialFromJson(const json& j) {
    std::string materialType = j["MaterialType"].get<std::string>();
    Material* mat = nullptr;

    if (materialType == "Diffuse")
        mat = new DiffuseMaterial;
    else if (materialType == "Refractive")
        mat = new RefractiveMaterial;
    else if (materialType == "Specular")  // Use obj.getType static?
        mat = new SpecularMaterial;


    mat->setEmittance(j["Emittance"].get<DoubleVec3D>());
    mat->setSpecificParametersJson(j["SpecificParameters"]);

    return mat;
}

void to_json(json& j, const Object3D& obj) {
    j = json{ {"ObjectType", obj.getType()}, {"Material", *(obj.getMaterial())}, {"Location", obj.getLocationJson()} };
}

Object3D* importObject3DFromJson(const json& j) {
    std::string objectType = j["ObjectType"].get<std::string>();
    Object3D* obj = nullptr;

    if (objectType == "Sphere")
        obj = new Sphere;
    else if (objectType == "Triangle")
        obj = new Triangle;

    obj->setMaterial(importMaterialFromJson(j["Material"]));
    obj->setLocationJson(j["Location"]);

    return obj;
}

// File manipulation
bool fileExists(std::string fileName) {
    std::ifstream f(fileName.c_str());
    return f.good();
}

std::string formatFileName(std::string fileName, std::string extension) {
    if (extension[0] != '.')
        extension = "." + extension;

    if (fileName.size() < extension.size())
        return fileName + extension;

    int extensionBeginningInFileName = fileName.size() - extension.size();

    for (int i = 0; i < extension.size(); i++) {
        if (!(std::tolower(fileName[extensionBeginningInFileName + i]) == std::tolower(extension[i]))) {
            return fileName + extension;
        }
    }

    return fileName;
}
