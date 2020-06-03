# Sentiment Analysis of Covid-19 on both China & America using NLTK

## Introduction
* Analyze both Weibo & Twitter from `3/10/2020 - 4/10/2020`
* Run scrawlers once every day
* Collect all topics relevant to Covid-19
* **Sentiment Analysis:** Analyze attitudes of Covid-19 by Users


## Features
* Data collection
* Diagrams showing Trending and Growth Rate
* Implement WordCloud
* Public Opinion Analysis on Covid-19


## Processing
1. Data Collection
    1. Weibo Scrawler implements BeautifulSoup to request url to search all top trending *"resou"*, and generate readable form to csv file using Pandas.
    2. Twitter Scrawler accesses Twitter API *"Tweepy"* to collect all most popular tweets under the top trending topics. Then generate readable form to csv file using Pandas.
    
2. Data Extraction
    1. Simply create lists of keywords regarding to Covid-19 on both English & Chinese versions. 
    2. Extract all data containing keywords from csv files. 
    
3. Growth Rate
    1. Calculate proportional between topics related to Covid-19 and all topics.
    2. Count number of topics related to Covid-19 every day to see the trending regarding to Covid-19 by users.

4. Model Training
    1. Twitter
        1. Implement SL_Feature for the model.
        2. Clean up data related to Covid-19 on Twitter: Tokenize, removing stopwords.
        3. Creating test & train set for model.
        4. The Accuracy: 78.2%.
        
    2. Weibo
        1. Implement bixin API as model to analyze Chinese sentences.
        2. reference is [here](https://github.com/bung87/bixin)
        
5. Sentiment Analysis
    1. Invoke both models of Twitter & Weibo to analysis all topics of Covid-19 on Twitter & Weibo, respectively.
    2. Import WordCould to view the top Unigram & Bigram on both Twitter & Weibo.
    3. Compare Positive & Negative on bar charts.
    4. Analyze attitudes (growth rate or trending) of people on Covid-19 .
 
