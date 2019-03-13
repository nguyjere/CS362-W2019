

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }
	
   public void testManualNull()
   {
	   String fakeNull = null;
	   UrlValidator urlVal = new UrlValidator();
	   assertFalse(urlVal.isValid(fakeNull));
   }
   
   public void testManualPattern()
   {
	   UrlValidator urlVal = new UrlValidator();
	   
	   //nothing close to pattern
	   assertFalse(urlVal.isValid("this is not a URL pattern"));
	   
	   //true pattern
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("ftp://www.google.com"));
	   
	   //missing scheme
	   assertFalse(urlVal.isValid("www.google.com"));
	   
	   //invalid pattern
	   assertFalse(urlVal.isValid("http:/www.google.com"));
	   assertFalse(urlVal.isValid("https://google"));
	   assertFalse(urlVal.isValid("ftp://com"));
	   
   }
   
   public void testManualSchemes()
   {
	   String afterScheme = "://www.example.com";
	   
	   //default schemes
	   UrlValidator urlVal = new UrlValidator();
	   
	   //default schemes should pass, non should fail
	   assertTrue(urlVal.isValid("https" + afterScheme));
	   assertTrue(urlVal.isValid("http" + afterScheme ));
	   assertTrue(urlVal.isValid("ftp" + afterScheme));
	   assertFalse(urlVal.isValid("foo" + afterScheme));
	   assertFalse(urlVal.isValid("bar" + afterScheme));
	   assertFalse(urlVal.isValid("BAZ" + afterScheme));
	   
	   //test with schemes declared
	   String[] schemes = {"foo", "bar", "BAZ"};
	   urlVal = new UrlValidator(schemes);
	   
	   //declared schemes should pass, non decalred should fail
	   assertFalse(urlVal.isValid("https" + afterScheme));
	   assertFalse(urlVal.isValid("http" + afterScheme ));
	   assertFalse(urlVal.isValid("ftp" + afterScheme));
	   assertTrue(urlVal.isValid("foo" + afterScheme));
	   assertTrue(urlVal.isValid("bar" + afterScheme));
	   assertTrue(urlVal.isValid("BAZ" + afterScheme));
	   
   }
   
   public void testManualAuth() {
	   
	   UrlValidator urlVal = new UrlValidator();
	   
	   //valid authority
	   assertTrue(urlVal.isValid("http://www.sample.com"));
	   
	   //missing authority
	   assertFalse(urlVal.isValid("http://"));
	   assertFalse(urlVal.isValid("https://"));
	   assertFalse(urlVal.isValid("ftp://"));
	   
	   //garbage authority
	   assertFalse(urlVal.isValid("http://test"));
	   assertFalse(urlVal.isValid("https://test"));
	   assertFalse(urlVal.isValid("ftp://test"));
   }
 
   
   public void testManualPaths()
   {
	   //all schemes
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("http://www.google.com/test1"));
	   assertTrue(urlVal.isValid("http://www.google.com/t123"));
	   assertTrue(urlVal.isValid("http://www.google.com/$23"));
	   assertFalse(urlVal.isValid("http://www.google.com/..//file"));
	   assertFalse(urlVal.isValid("http://www.google.com/.."));
	   assertFalse(urlVal.isValid("http://www.google.com/test//file"));
	   assertFalse(urlVal.isValid("https://www.google.com/../"));
	   
   }
   
   public void testManualQueries()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("https://www.google.com/?action=view"));
	   assertTrue(urlVal.isValid("https://google.com/?action=edit&mode=up"));
   }
   
   public void testManualFrag()
   {
	   long options = UrlValidator.NO_FRAGMENTS + UrlValidator.ALLOW_ALL_SCHEMES;
	   UrlValidator urlVal = new UrlValidator(options);
	   assertFalse(urlVal.isValid("https://www.google.com/#/hello"));
	   assertTrue(urlVal.isValid("https://www.google.com/hello:"));
	   
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
