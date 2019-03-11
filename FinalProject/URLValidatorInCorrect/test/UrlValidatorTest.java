

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testSimplePaths()
   {
	   String[] paths = {"index", "index/", "index/etc/", "~index"};
	   UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   for (String path : paths) {
		   assertTrue(path, urlValidator.isValid("http://www.example.com/" + path));
	   }
   }
   
   public void testIpAddresses() {
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       for (int i = 0; i < 300; i++)
       {
    	   String url = String.format("https://%d.%d.%d.%d", i, i, i, i);
    	   if (i <= 255 || i == 0)
    	   {
    		   assertTrue(url, urlValidator.isValid(url));
    	   } else {
    		   assertFalse(url, urlValidator.isValid(url));
    	   }
       }
   }

   public void testSchemes()
   {
	   String[] schemes = {"foo", "bar", "BAZ"};
	   UrlValidator urlValidator = new UrlValidator(schemes);
	   for (String scheme : schemes) {
		   assertTrue(scheme, urlValidator.isValid(scheme + "://www.example.com/"));
	   }
   } 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
