#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager
{
public:
    FileManager();

    /**
     * @brief Saves a serialized model.
     */
    void Save();

    /**
     * @brief Serializes a model.
     */
    Serialize();

    /**
     * @brief Loads a deserialized file.
     */
    void Load();

    /**
     * @brief Deserializes a file.
     */
    Deserialize();


};

#endif // FILEMANAGER_H
