#! /usr/bin/python

import unittest
import ArxmlParser

NAME_SPACE = 'http://autosar.org/schema/r4.0'

class TestPort(unittest.TestCase):
    """ArxmlParser testcases"""
    def setUp(self):
        self.parser = ArxmlParser.ArxmlParser(NAME_SPACE)

    def test_impl_value_type(self):
        """test parsing value type"""
        self.parser.get_impl_types('arxml/DataTypes_test.arxml')

        found = False
        for _type in self.parser.type_array:
            if _type.name == 'Value_T':
                self.assertIsInstance(_type, ArxmlParser.ValueType)
                found = True

        self.assertTrue(found)


    def test_impl_array_type(self):
        """test if array type was fond in the parsed data, then check that 
        the array element type in also in list of types
        """
        self.parser.get_impl_types('arxml/DataTypes_test.arxml')

        found = False
        for _type in self.parser.type_array:
            if _type.name == 'Array_T':
                self.assertIsInstance(_type, ArxmlParser.ArrayType)
                found = True

                self.assertIsInstance(_type.element_type, ArxmlParser.ValueType)
                element_type_name = _type.element_type.name
                self.assertTrue(element_type_name == 'ArrayElement_T')
                self.assertTrue(_type.size == 5)

        self.assertTrue(found)

        #test if the array element type is also in list
        found = False
        for _type in self.parser.type_array:
            if _type.name == element_type_name:
                found = True

        self.assertTrue(found)

    def test_impl_struct_type(self):
        """test if struct type was fond in the parsed data, then check that 
        each of the struct element types is also in list of types
        """
        self.parser.get_impl_types('arxml/DataTypes_test.arxml')

        found = False
        for _type in self.parser.type_array:
            if _type.name == 'Struct_T':
                self.assertIsInstance(_type, ArxmlParser.StructType)
                found = True

                for key, element in _type.element_dict.items():
                    element_found = False
                    for element_type in self.parser.type_array:
                        if element_type.name == element.name:
                            element_found = True

                    self.assertTrue(element_found)

        self.assertTrue(found)

    def test_compu(self):
        print(self.parser.get_compu_methods('arxml/DataTypes_test.arxml'))


        
if __name__ == '__main__':
    unittest.main()
