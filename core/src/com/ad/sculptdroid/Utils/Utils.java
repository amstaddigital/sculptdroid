package com.ad.sculptdroid.Utils;


import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

/**
 *
 * A collection of Utility methods converted
 * to Java from JavaScript. Some can be transposed
 * but others are built in to Java so no need.
 *
 * Original at sculptdroid/src/misc/Utils.js
 *
 * @author James Lennon
 * @version 1.00, 28 Nov 2018
 */

public class Utils {

    // Scale factor
    public float Scale = 100.0f;

    // Just a big integer to flag invalid positive index <-- No clue wtf the original author meant
    public long Tri_Index = 4294967295L;

    /*
        TODO: Unconverted variables
        Utils.TAG_FLAG = 1; // flag value for comparison (always >= tags values)
        Utils.SCULPT_FLAG = 1; // flag value for sculpt (always >= tags values)
        Utils.STATE_FLAG = 1; // flag value for states (always >= tags values)
        Utils.cursors = {};
        Utils.cursors.dropper = 'url(resources/dropper.png) 5 25, auto';
    */

    /**
     * Color Conversion from Linear to SRGB
     *
     * @param x the value {@code double} to convert
     * @return converted {@code double} of x
     */
    public double linearToSRGB1(double x) {
        return x < 0.0031308 ?  x * 12.92 : 1.055 * Math.pow(x, 1.0 / 2.4) - 0.055;
    }

    /**
     * Color Conversion from sRGB to Linear
     *
     * @param x the value {@code double} to convert
     * @return converted {@code double} of x
     */
    public double sRGBToLinear1(double x) {
        return x < 0.04045 ? x * (1.0 / 12.92) : Math.pow((x + 0.055) * (1.0 / 1.055), 2.4);
    }

    /**
     * Checks if passed value is a power of two
     *
     * @param x the value {@code int} to check
     * @return {@code boolean}
     */
    public boolean isPowerOfTwo(int x) {
        return x%2 == 0;
    }

    /**
     * Checks if passed value is a power of two
     *
     * @param x the value {@code float} to check
     * @return {@code boolean}
     */
    public boolean isPowerOfTwo(float x) {
        return x%2 == 0;
    }

    /**
     * Checks if passed value is a power of two
     *
     * @param x the value {@code double} to check
     * @return {@code boolean}
     */
    public boolean isPowerOfTwo(double x) {
        return x%2 == 0;
    }

    /**
     * Returns the next power of two above given value
     *
     * @param x the value {@code double}
     * @return {@code int}
     */
    public int nextHighPowerOfTwo(int x) {
        x--;
        for(int i = 0; i < 32; i <<= 1) {
            x = x | x >> i;
        }
        return x + 1;
    }

    /**
     * Takes the unique values of given arraylist and sorts them
     *
     * @param arr
     * @return {@code ArrayList<T>} sorted unique ArrayList
     */
    public ArrayList<Integer> uniqueSortArray(ArrayList<Integer> arr) {
        // Ensures duplicate removal by nature
        Set<Integer> setList = new LinkedHashSet<Integer>(arr);

        // Clear out the passed array
        arr.clear();

        // Add unique values back to the original array
        arr.addAll(setList);

        // Sort numerically
        Collections.sort(arr);

        return arr;
    }

    public ArrayList<Integer> intersectionArray(ArrayList<Integer> arr1, ArrayList<Integer> arr2) {
        arr1.retainAll(arr2);
        return arr1;
    }


    /*
        TODO: Unconverted methods
        Utils.extend = function (dest, src) {
          var keys = Object.keys(src);
          for (var i = 0, l = keys.length; i < l; ++i) {
            var key = keys[i];
            if (dest[key] === undefined) dest[key] = src[key];
          }
          return dest;
        };

        Utils.invert = function (obj) {
          var keys = Object.keys(obj);
          var inv = {};
          for (var i = 0, nbkeys = keys.length; i < nbkeys; ++i)
            inv[obj[keys[i]]] = keys[i];
          return inv;
        };

        Utils.replaceElement = function (array, oldValue, newValue) {
          for (var i = 0, l = array.length; i < l; ++i) {
            if (array[i] === oldValue) {
              array[i] = newValue;
              return;
            }
          }
        };

        Utils.removeElement = function (array, remValue) {
          for (var i = 0, l = array.length; i < l; ++i) {
            if (array[i] === remValue) {
              array[i] = array[l - 1];
              array.pop();
              return;
            }
          }
        };

        Utils.appendArray = function (array1, array2) {
          var nb1 = array1.length;
          var nb2 = array2.length;
          array1.length += nb2;
          for (var i = 0; i < nb2; ++i)
            array1[nb1 + i] = array2[i];
        };

     */

}
