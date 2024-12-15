package dataClasses

import java.io.File
import java.io.IOException
import java.util.HashMap

/**
 * This class provides a way to read and parse CSV or TXT files into a data structure representing
 * locations and their distances.
 *
 * Imports:
 *  - [File][java.io.File]
 *  - [IOException][java.io.IOException]
 *  - [HashMap][java.util.HashMap]
 *
 * Internal Imports:
 *  - [Pair][dataClasses.Pair]
 *
 * Methods:
 *  - [read][dataClasses.FileReader.read]
 *  - [createMap][dataClasses.FileReader.createMap]
 *
 * Assumptions:
 *  - The file is either a CSV or TXT
 *  - The file has three columns: location1, location2, and distance.
 *  - The distance column contains integer values.
 *
 *  @author Naomi
 */
class FileReader
{
    /**
     * This function tries to read a [file][File] at the given [filePath], if it fails it will throw an
     * [IOException][java.io.IOException], before reading the data using the [forEachLine][java.io.File.forEachLine]
     * method to iterate over each line of the file, reading the contents of the line and then splitting the contents
     * at the ", " delimiter and storing the split items in the nested list. The nested list being a [mutableListOf]
     * containing a [List] of [String]'s
     *
     * @param filePath The path to the file.
     * @return A nested list containing the parsed data.
     * @throws IOException If an error occurs while reading the file.
     *
     * @author Naomi
     */
    fun read(filePath: String): List<List<String>>
    {
        val nestedList = mutableListOf<List<String>>()

        try
        {
            File(filePath).forEachLine { line ->
                val items = line.split(", ")
                nestedList.add(items.toList())
            }
        } catch (e: IOException) {
            throw IOException("Error reading $filePath", e)
        }
        return nestedList
    }

    /**
     * This function converts the parsed [data] into a [Map] where each key is a [location][String], it will iterate
     * over the [data] using [forEach] and splitting the row values between 3 values while converting the 3rd to an
     * Integer with [toInt]. This is followed by the function checking if the first value already exists as a key
     * in the [Map] using [computeIfAbsent][HashMap.computeIfAbsent], if the key doesn't exit it creates it with its
     * value being a [mutableListOf] of [Pair]'s which contain the second and third values. Then does the same with
     * the second value, checking if it's a key, if not then it creates it and adds the first and third value as a [Pair]
     * and storing it in its value.
     *
     * @param data The parsed data from the file.
     * @return A map representing the relational data.
     *
     * @author Naomi
     */
    fun createMap(data: List<List<String>>): Map<String, List<Pair<String, Int>>>
    {
        val locationMap = HashMap<String, MutableList<Pair<String, Int>>>()

        data.forEach { row ->
            val location1 = row[0]
            val location2 = row[1]
            val distance = row[2].toInt()

            locationMap.computeIfAbsent(location1) { mutableListOf() }.add(Pair(location2, distance))
            locationMap.computeIfAbsent(location2) { mutableListOf() }.add(Pair(location1, distance))
        }
        return locationMap
    }
}
