#include "Interface.h"


// Main interface
void displayCommands() {
    bool isObjectsPages = currentPage == Page::ObjectsPage;

    availableCommandsHeader();

    if (isObjectsPages) {
        std::cout << "- a: add an object group" << std::endl;
        std::cout << "- d: delete an object group" << std::endl;
    }
    
    if (isObjectsPages) {
        std::cout << "- g: merge two objects groups" << std::endl;
        std::cout << "- i: import an object from a FBX file as an objects group" << std::endl;
        std::cout << "- l: load object groups from a " << OBJECTS_SAVE_EXTENSION << " file and add them to current ones" << std::endl;
    }
    else {
        std::cout << "- l: load parameters from a " << PARAMETERS_SAVE_EXTENSION << " file and overwrite current ones" << std::endl;
    }

    std::cout << "- m: modify a" << (isObjectsPages ? "n object group" : " parameter") << std::endl;
    std::cout << "- p: switch to " << (isObjectsPages ? "parameters" : "objects") << " page" << std::endl;
    std::cout << "- r: start the rendering" << std::endl;

    if (isObjectsPages)
        std::cout << "- s: save current object groups to a " << OBJECTS_SAVE_EXTENSION << " file" << std::endl;
    else
        std::cout << "- s: save current parameters to a " << PARAMETERS_SAVE_EXTENSION << " file" << std::endl;
    
    std::cout << "- t: load a picture from a " << PICTURE_SAVE_EXTENSION_JSON << " file" << std::endl;
    std::cout << "- x: exit this program" << std::endl;
}


void receiveAndExecuteGeneralCommands() {
    bool isParametersPage = currentPage == Page::ParametersPage;

    std::cout << std::endl;
    if (commandWasInvalid) {
        std::cout << INVALID_COMMAND << std::endl;
    }
    char command = getLowerCaseCharFromUser();

    if (commandWasInvalid) {
        // Reprint everything to remove the "invalid command"
        printAll();
        std::cout << std::endl << PROMPT << command << std::endl;
        commandWasInvalid = false;
    }
    std::cout << std::endl;


    switch (command) {
    case 'p': {
        if (isParametersPage)
            currentPage = Page::ObjectsPage;
        else
            currentPage = Page::ParametersPage;
        return;
    }
    case 'r': {
        clearScreenPrintHeader();
        Picture* pict = scene.render();

        if (pict->getRenderTime() > smallestRenderTime4PictBackup) {
            double beginningTime = getCurrentTimeSeconds();
            std::cout << "Backing the picture up...";

            json jsonOutput = *pict;

            std::ofstream file;
            file.open(backupFileName);
            file << std::setw(4) << jsonOutput << std::endl;
            file.close();

            std::cout << "\rPicture succesffuly backed up to " << backupFileName << " in " << getCurrentTimeSeconds() - beginningTime << "s " << std::endl;
            std::cout << std::endl;
        }

        std::cout << "\a";  // Make noise to notify end of rendering
        getStringFromUser("Press enter to continue");

        pict->modify();
        delete pict;
        return;
    }
    case 't': {
        std::string fileName = getStringFromUser("What is the name of the " + PICTURE_SAVE_EXTENSION_JSON + " file from which the picture will be loaded?");
        fileName = formatFileName(fileName, PICTURE_SAVE_EXTENSION_JSON);
        std::cout << std::endl;

        if (!fileExists(fileName)) {
            std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
            return;
        }

        double beginningTime = getCurrentTimeSeconds();
        json jsonInput;

        std::ifstream file;
        try {
            file.open(fileName);
            file >> jsonInput;
            file.close();

            Picture pict = importPictureFromJson(jsonInput);
            std::cout << "Successfully loaded picture from " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");

            pict.modify();

        } catch (const json::exception& e) {
            if (file.is_open())
                file.close();
            std::cout << "The file " << fileName << " is corrupted." << std::endl << "Error: " << e.what() << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
        }
        return;
    }
    case 'x': {
        std::cout << "Have a nice day!" << std::endl;
        exit(0);
    }
    default:
        if (isParametersPage)
            executeParametersCommands(command);
        else
            executeObjectsCommands(command);
        return;
    }
}


void executeParametersCommands(char command) {
    switch (command) {
    case  'l': {
        std::string fileName = getStringFromUser("What is the name of the " + PARAMETERS_SAVE_EXTENSION + " file from where the parameters will be loaded?");
        fileName = formatFileName(fileName, PARAMETERS_SAVE_EXTENSION);
        std::cout << std::endl;
        double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

        bool exists = fileExists(fileName);
        if (!exists) {
            std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
            return;
        }

        json jsonInput;

        std::ifstream file;
        file.open(fileName);  // File could change name -> need to make another try catch
        try {
            file >> jsonInput;
            file.close();

            json jsonCamera = jsonInput["Camera"];
            camera.setNumberPixelsX(jsonCamera["NumberPixelsX"].get<unsigned int>());
            camera.setNumberPixelsY(jsonCamera["NumberPixelsY"].get<unsigned int>());
            camera.setOrigin(jsonCamera["Origin"].get<DoubleVec3D>());
            camera.setFocal(jsonCamera["Focal"].get<DoubleVec3D>());

            json jsonBasicParameters = jsonInput["BasicParameters"];
            scene.setSamplePerPixel(jsonBasicParameters["SamplePerPixel"].get<unsigned int>());
            scene.setMinBounces(jsonBasicParameters["MinBounces"].get<unsigned int>());

            json jsonOptimisationParameters = jsonInput["OptimisationParameters"];
            scene.setNumberThreads(jsonOptimisationParameters["NumberThreads"].get<unsigned int>());
            scene.setRussianRoulette(jsonOptimisationParameters["RussianRoulette"].get<bool>());
            scene.setRrStopProbability(jsonOptimisationParameters["RrStopProbability"].get<double>());
            scene.setNextEventEstimation(jsonOptimisationParameters["NextEventEstimation"].get<bool>());
            scene.setKDTree(jsonOptimisationParameters["KDTree"].get<bool>());
            scene.setKDMaxDepth(jsonOptimisationParameters["KDMaxDepth"].get<unsigned int>());
            scene.setKDMaxObjectNumber(jsonOptimisationParameters["KDMaxObjectNumber"].get<unsigned int>());

            std::cout << "Successfully loaded parameters from " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
        }
        catch (const json::exception& e) {
            if (file.is_open())
                file.close();
            std::cout << "The file " << fileName << " is corrupted." << std::endl << "Error: " << e.what() << std::endl << std::endl;
        }

        getStringFromUser("Press enter to continue.");
        return;
    }
    case 'm': {
        // Modify a parameter
        while (true) {
            int index = getIntFromUser("What is the index of the parameter you want to modify (-1 = cancel) " + POSITIVE_INT_INFO);
            if (0 <= index && index <= 12)
                std::cout << std::endl;
            switch (index) {
            case -1: return;
            case 0: camera.setNumberPixelsX(getUnsignedIntFromUser("What is the new camera width? " + POSITIVE_INT_INFO)); return;
            case 1: camera.setNumberPixelsY(getUnsignedIntFromUser("What is the new camera height? " + POSITIVE_INT_INFO)); return;
            case 2: camera.setOrigin(getXYZDoubleVec3DFromUser("What is the new camera origin?")); return;
            case 3: camera.setFocal(getXYZDoubleVec3DFromUser("What is the new camera focal?")); return;
            case 4: scene.setSamplePerPixel(getUnsignedIntFromUser("What is the new number of sample per pixel? " + POSITIVE_INT_INFO)); return;
            case 5: scene.setMinBounces(getUnsignedIntFromUser("What is the new minimum number of ray bounces? (there can be less if nothing is hit) " + POSITIVE_INT_INFO)); return;
            case 6: scene.setNumberThreads(getUnsignedIntFromUser("What is the new number of threads that will used during the rendering? " + POSITIVE_INT_INFO)); return;
            case 7: scene.setRussianRoulette(getBoolFromUser("Will the russian roulette path termination algorithm be used? " + BOOL_INFO)); return;
            case 8:
                while (true) {
                    double probability = getPositiveDoubleFromUser("What is the new stop probability for the russian roulette path termination algorithm? (positive number between 0 and 1)");
                    if (probability >= 0 && probability <= 1) {
                        scene.setRrStopProbability(probability);
                        return;
                    }
                    std::cout << "This number is not between 0 and 1!" << std::endl << std::endl;
                }
            case 9: scene.setNextEventEstimation(getBoolFromUser("Will the next event estimation algorithm be used? " + BOOL_INFO)); return;
            case 10: scene.setKDTree(getBoolFromUser("Will a k-d tree be used? " + BOOL_INFO)); return;
            case 11: scene.setKDMaxDepth(getUnsignedIntFromUser("What is the new maximum k-d tree depth? " + POSITIVE_INT_INFO)); return;
            case 12: scene.setKDMaxObjectNumber(getUnsignedIntFromUser("What is the new maximum of objects contained in a k-d tree leaf? " + POSITIVE_INT_INFO)); return;
            default: std::cout << "This index is invalid!" << std::endl << std::endl;
            }
        }
    }
    case 's': {
        std::string fileName = getStringFromUser("What is the name of the " + PARAMETERS_SAVE_EXTENSION + " file in which the parameters will be saved?");
        std::cout << std::endl;
        fileName = formatFileName(fileName, PARAMETERS_SAVE_EXTENSION);

        if (fileExists(fileName)) {
            bool continue_ = getBoolFromUser("The file " + fileName + " already exists, do you want to continue? " + BOOL_INFO);
            if (!continue_)
                return;
        }
        double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

        json jsonOutput = {
            {"Camera", {
                {"NumberPixelsX", camera.getNumberPixelsX()},
                {"NumberPixelsY", camera.getNumberPixelsY()},
                {"Focal", camera.getFocal()},
                {"Origin", camera.getOrigin()}
                }
            },
            {"BasicParameters", {
                {"SamplePerPixel", scene.getSamplePerPixel()},
                {"MinBounces", scene.getMinBounces()}
                }
            },
            {"OptimisationParameters", {
                {"NumberThreads", scene.getNumberThreads()},
                {"RussianRoulette", scene.getRussianRoulette()},
                {"RrStopProbability", scene.getRrStopProbability()},
                {"NextEventEstimation", scene.getNextEventEstimation()},
                {"KDTree", scene.getKDTree()},
                {"KDMaxDepth", scene.getKDMaxDepth()},
                {"KDMaxObjectNumber", scene.getKDMaxObjectNumber()}
                }
            }
        };

        std::ofstream file;
        file.open(fileName);
        file << std::setw(4) << jsonOutput << std::endl;
        file.close();

        std::cout << "Successfully saved objects to " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
        getStringFromUser("Press enter to continue.");
        return;
    }
    default:
        commandWasInvalid = true;
    }
}


void executeObjectsCommands(char command) {
    switch (command) {
    case 'a': {
        Object3DGroup newGroup = Object3DGroup::create();
        objectGroups.push_back(newGroup);
        objectGroups[objectGroups.size() - 1].modify();
        return;
    }
    case 'd': {
        if (objectGroups.size() >= 1) {
            while (true) {
                int index = getIntFromUser("What is the index of the objects groups you want to delete? (-1 = cancel / -2 = delete all)");
                if (index == -1)
                    return;
                if (index == -2) {
                    std::cout << std::endl;
                    bool confirmation = getBoolFromUser("Do you confirm the deletion of all the objects groups? " + BOOL_INFO);
                    if (confirmation)
                        scene.resetObjectGroups();
                    return;
                }
                if (index >= 0 && index < objectGroups.size()) {
                    std::cout << std::endl;
                    bool confirmation = getBoolFromUser("Do you confirm the deletion of this objects group? " + BOOL_INFO);
                    if (confirmation)
                        objectGroups.erase(objectGroups.begin() + index);
                    return;
                }
                std::cout << "This index is invalid!" << std::endl << std::endl;
            }
        }
        else
            commandWasInvalid = true;
        return;
    }
    case 'g': {
        if (objectGroups.size() >= 2) {
            while (true) {
                int index1 = getIntFromUser("What is the index of the first objects group? (-1 = cancel)");
                if (index1 == -1)
                    return;
                if (index1 >= 0 && index1 < objectGroups.size()) {
                    while (true) {
                        std::cout << std::endl;
                        int index2 = getIntFromUser("What is the index of the second objects group? (-1 = cancel)");
                        if (index2 == -1)
                            return;
                        if (index2 == index1)
                            std::cout << "The second index must be different from the first one" << std::endl << std::endl;
                        else if (index2 >= 0 && index2 < objectGroups.size()) {
                            std::cout << std::endl;
                            std::string newName = getStringFromUser("What is the name of the merged objects group?");
                            objectGroups[index1].merge(objectGroups[index2]);
                            Object3DGroup newObject = objectGroups[index1];

                            objectGroups.erase(objectGroups.begin() + std::max(index1, index2));
                            objectGroups.erase(objectGroups.begin() + std::min(index1, index2));

                            newObject.setName(newName);
                            objectGroups.push_back(newObject);
                            return;
                        }
                        else
                            std::cout << "This index is invalid" << std::endl << std::endl;
                    }
                }
                std::cout << "This index is invalid" << std::endl << std::endl;
            }
        }
        else
            commandWasInvalid = true;
        return;
    }
    case 'i': {
        std::string fileName = getStringFromUser("What is the name of the " + FBX_EXTENSION + " file?");
        fileName = formatFileName(fileName, ".fbx");
        std::cout << std::endl;
        bool exists = fileExists(fileName);

        if (!exists) {
            std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
            return;
        }

        std::string name = getStringFromUser("How do you want to call the objects group?");
        std::cout << std::endl;
        Material* material = createMaterial();
        scene.importFBX(fileName.c_str(), material, name);
        std::cout << std::endl;
        getStringFromUser("Press enter to continue.");
        return;
    }
    case  'l': {
        std::string fileName = getStringFromUser("What is the name of the " + OBJECTS_SAVE_EXTENSION + " file from where the object groups will be loaded?");
        fileName = formatFileName(fileName, OBJECTS_SAVE_EXTENSION);
        std::cout << std::endl;
        double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

        bool exists = fileExists(fileName);
        if (!exists) {
            std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
            getStringFromUser("Press enter to continue.");
            return;
        }

        json jsonInput;

        std::ifstream file;
        file.open(fileName);  // File could change name -> need to make another try catch
        try {
            file >> jsonInput;
            file.close();

            for (json jsonGroup : jsonInput) {
                objectGroups.push_back(jsonGroup.get<Object3DGroup>());
            }
            std::cout << "Successfully loaded objects from " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;

        }
        catch (const json::exception& e) {
            if (file.is_open())
                file.close();
            std::cout << "The file " << fileName << " is corrupted." << std::endl << "Error: " << e.what() << std::endl << std::endl;
        }

        getStringFromUser("Press enter to continue.");
        return;
    }
    case 'm': {
        if (objectGroups.size() >= 1) {
            while (true) {
                int index = getIntFromUser("What is the index of the objects groups you want to modify (-1 = cancel) " + POSITIVE_INT_INFO);

                if (index == -1)
                    return;

                if (index < objectGroups.size()) {
                    objectGroups[index].modify();
                    return;
                }
                else {
                    std::cout << "This index is invalid!" << std::endl << std::endl;
                }
            }
        }
        else
            commandWasInvalid = true;
        return;
    }
    case 's': {
        std::string fileName = getStringFromUser("What is the name of the " + OBJECTS_SAVE_EXTENSION + " file in which the object groups will be saved?");
        std::cout << std::endl;
        fileName = formatFileName(fileName, OBJECTS_SAVE_EXTENSION);

        if (fileExists(fileName)) {
            bool continue_ = getBoolFromUser("The file " + fileName + " already exists, do you want to continue? " + BOOL_INFO);
            if (!continue_)
                return;
        }
        double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

        json jsonOutput;
        for (Object3DGroup group : objectGroups) {
            jsonOutput.push_back(group);
        }

        std::ofstream file;
        file.open(fileName);
        file << std::setw(4) << jsonOutput << std::endl;
        file.close();

        std::cout << "Successfully saved object groups to " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
        getStringFromUser("Press enter to continue.");
        return;
    }
    default:
        commandWasInvalid = true;
    }
}


void printAll() {
    clearScreenPrintHeader();
    if (currentPage == Page::ParametersPage)
        scene.displayParametersPage();
    else
        scene.displayObjectsPage();
    displayCommands();
}

void initInterface() {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    scene.resetObjectGroups();
    scene.defaultScene();

    while (true) {
        printAll();
        receiveAndExecuteGeneralCommands();
    }
}
