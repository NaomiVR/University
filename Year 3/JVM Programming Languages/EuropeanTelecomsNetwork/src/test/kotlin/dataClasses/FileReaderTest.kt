package dataClasses

import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertThrows
import org.junit.jupiter.api.Assertions.*

import java.io.IOException

class FileReaderTest
{
    private lateinit var fileReader: FileReader

    @BeforeEach
    fun setUp()
    {
        fileReader = FileReader()
    }

    @Test
    fun testThrowIOException()
    {
        val nonExistentFilePath = "doesnt_exist.txt"
        val exception = assertThrows<IOException>
        {
            fileReader.read(nonExistentFilePath)
        }
        assertTrue(exception.message!!.contains("doesnt_exist.txt"))
    }

    @Test
    fun testRead()
    {
        val filePath = "src/test/resources/test_data"
        val expectedData = listOf(
            listOf("A", "B", "5"),
            listOf("C", "D", "10")
        )

        val actualData = fileReader.read(filePath)

        assertEquals(expectedData, actualData)
    }

    @Test
    fun testCreateMap()
    {
        val data = listOf(
            listOf("A", "B", "5"),
            listOf("C", "D", "10"),
            listOf("B", "A", "3")
        )

        val expectedMap = mapOf(
            "A" to listOf(Pair("B", 5), Pair("B", 3)),
            "B" to listOf(Pair("A", 5), Pair("A", 3)),
            "C" to listOf(Pair("D", 10)),
            "D" to listOf(Pair("C", 10))
        )

        val actualMap = fileReader.createMap(data)

        assertEquals(expectedMap, actualMap)
    }
}